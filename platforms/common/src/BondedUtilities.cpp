/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit.                   *
 * See https://openmm.org/development.                                        *
 *                                                                            *
 * Portions copyright (c) 2011-2023 Stanford University and the Authors.      *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify       *
 * it under the terms of the GNU Lesser General Public License as published   *
 * by the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Lesser General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.      *
 * -------------------------------------------------------------------------- */

#include "openmm/common/BondedUtilities.h"
#include "openmm/common/ComputeContext.h"
#include "openmm/OpenMMException.h"
#include <iostream>

using namespace OpenMM;
using namespace std;

BondedUtilities::BondedUtilities(ComputeContext& context) : context(context), numForceBuffers(0), maxBonds(0), hasInitializedKernels(false) {
}

void BondedUtilities::addInteraction(const vector<vector<int> >& atoms, const string& source, int group) {
    if (atoms.size() > 0) {
        forceAtoms.push_back(atoms);
        forceSource.push_back(source);
        forceGroup.push_back(group);
        // Get the group of Topology this Force belongs to.
        int topologyGroup = group / 32;
        // Get the internal force group in its Topology.
        int internalForceGroup = group % 32;
        int allGroup = 1 << internalForceGroup;
        // A topologyGroup already exists.
        if (allGroups.size() > topologyGroup)
            allGroups[topologyGroup] |= allGroup;
        // A new topologyGroup. 
        else {
            allGroups.resize((topologyGroup+1), 0);
            allGroups.back() = allGroup;
        }
    }
}

string BondedUtilities::addArgument(ArrayInterface& data, const string& type) {
    arguments.push_back(&data);
    argTypes.push_back(type);
    return "customArg"+context.intToString(arguments.size());
}

string BondedUtilities::addEnergyParameterDerivative(const string& param) {
    // See if the parameter has already been added.
    
    int index;
    for (index = 0; index < energyParameterDerivatives.size(); index++)
        if (param == energyParameterDerivatives[index])
            break;
    if (index == energyParameterDerivatives.size())
        energyParameterDerivatives.push_back(param);
    context.addEnergyParameterDerivative(param);
    return string("energyParamDeriv")+context.intToString(index);
}

void BondedUtilities::addPrefixCode(const string& source) {
    for (int i = 0; i < (int) prefixCode.size(); i++)
        if (prefixCode[i] == source)
            return;
    prefixCode.push_back(source);
}

void BondedUtilities::initialize(const System& system) {
    int numForces = forceAtoms.size();
    hasInteractions = (numForces > 0);
    if (!hasInteractions)
        return;
    
    // Build the lists of atom indices.
    
    atomIndices.resize(numForces);
    for (int i = 0; i < numForces; i++) {
        int numBonds = forceAtoms[i].size();
        int numAtoms = forceAtoms[i][0].size();
        int numArrays = (numAtoms+3)/4;
        int startAtom = 0;
        atomIndices[i].resize(numArrays);
        for (int j = 0; j < numArrays; j++) {
            int width = min(numAtoms-startAtom, 4);
            int paddedWidth = (width == 3 ? 4 : width);
            vector<unsigned int> indexVec(paddedWidth*numBonds);
            for (int bond = 0; bond < numBonds; bond++) {
                for (int atom = 0; atom < width; atom++)
                    indexVec[bond*paddedWidth+atom] = forceAtoms[i][bond][startAtom+atom];
            }
            atomIndices[i][j].initialize(context, numBonds, 4*paddedWidth, "bondedIndices");
            atomIndices[i][j].upload(&indexVec[0]);
            startAtom += width;
        }
    }

    // Create the kernel.

    stringstream s;
    for (int i = 0; i < (int) prefixCode.size(); i++)
        s<<prefixCode[i];
    s<<"KERNEL void computeBondedForces(GLOBAL mm_ulong* RESTRICT forceBuffer, GLOBAL mixed* RESTRICT energyBuffer, GLOBAL const real4* RESTRICT posq, GLOBAL const int* RESTRICT groups, real4 periodicBoxSize, real4 invPeriodicBoxSize, real4 periodicBoxVecX, real4 periodicBoxVecY, real4 periodicBoxVecZ";
    for (int force = 0; force < numForces; force++) {
        for (int i = 0; i < (int) atomIndices[force].size(); i++) {
            int indexWidth = atomIndices[force][i].getElementSize()/4;
            string indexType = (indexWidth == 1 ? "unsigned int" : "uint"+context.intToString(indexWidth));
            s<<", GLOBAL const "<<indexType<<"* RESTRICT atomIndices"<<force<<"_"<<i;
        }
    }
    for (int i = 0; i < (int) arguments.size(); i++)
        s<<", GLOBAL "<<argTypes[i]<<"* customArg"<<(i+1);
    if (energyParameterDerivatives.size() > 0)
        s<<", GLOBAL mixed* RESTRICT energyParamDerivs";
    s<<") {\n";
    s<<"mixed energy = 0;\n";
    for (int i = 0; i < energyParameterDerivatives.size(); i++)
        s<<"mixed energyParamDeriv"<<i<<" = 0;\n";
    for (int force = 0; force < numForces; force++)
        s<<createForceSource(force, forceAtoms[force].size(), forceAtoms[force][0].size(), forceGroup[force], forceSource[force]);
    s<<"energyBuffer[GLOBAL_ID] += energy;\n";
    const vector<string>& allParamDerivNames = context.getEnergyParamDerivNames();
    int numDerivs = allParamDerivNames.size();
    for (int i = 0; i < energyParameterDerivatives.size(); i++)
        for (int index = 0; index < numDerivs; index++)
            if (allParamDerivNames[index] == energyParameterDerivatives[i])
                s<<"energyParamDerivs[(GLOBAL_ID)*"<<numDerivs<<"+"<<index<<"] += energyParamDeriv"<<i<<";\n";
    s<<"}\n";
    map<string, string> defines;
    defines["PADDED_NUM_ATOMS"] = context.intToString(context.getPaddedNumAtoms());
    ComputeProgram program = context.compileProgram(s.str(), defines);
    kernel = program->createKernel("computeBondedForces");
    forceAtoms.clear();
    forceSource.clear();
}

string BondedUtilities::createForceSource(int forceIndex, int numBonds, int numAtoms, int group, const string& computeForce) {
    maxBonds = max(maxBonds, numBonds);
    string suffix1[] = {""};
    string suffix4[] = {".x", ".y", ".z", ".w"};
    stringstream s;
    int topologyGroup = group / 32 ;
    // if ((topologyGroup < groups.size()) && (groups[topologyGroup]&(1<<(group-32*topologyGroup))) != 0))
    // Note that here, the size of groups is groups[0].
    s<<"if (("<<topologyGroup<<" < "<<"groups[0]) && ((groups["<<(topologyGroup+1)<<"]&"<<(1<<(group-32*topologyGroup))<<") != 0))\n";
    s<<"for (unsigned int index = GLOBAL_ID; index < "<<numBonds<<"; index += GLOBAL_SIZE) {\n";
    int startAtom = 0;
    for (int i = 0; i < (int) atomIndices[forceIndex].size(); i++) {
        int indexWidth = atomIndices[forceIndex][i].getElementSize()/4;
        string* suffix = (indexWidth == 1 ? suffix1 : suffix4);
        string indexType = (indexWidth == 1 ? "unsigned int" : "uint"+context.intToString(indexWidth));
        s<<"    "<<indexType<<" atoms"<<i<<" = atomIndices"<<forceIndex<<"_"<<i<<"[index];\n";
        int atomsToLoad = min(indexWidth, numAtoms-startAtom);
        for (int j = 0; j < atomsToLoad; j++) {
            s<<"    unsigned int atom"<<(startAtom+j+1)<<" = atoms"<<i<<suffix[j]<<";\n";
            s<<"    real4 pos"<<(startAtom+j+1)<<" = posq[atom"<<(startAtom+j+1)<<"];\n";
        }
        startAtom += indexWidth;
    }
    s<<computeForce<<"\n";
    for (int i = 0; i < numAtoms; i++) {
        s<<"    ATOMIC_ADD(&forceBuffer[atom"<<(i+1)<<"], (mm_ulong) realToFixedPoint(force"<<(i+1)<<".x));\n";
        s<<"    ATOMIC_ADD(&forceBuffer[atom"<<(i+1)<<"+PADDED_NUM_ATOMS], (mm_ulong) realToFixedPoint(force"<<(i+1)<<".y));\n";
        s<<"    ATOMIC_ADD(&forceBuffer[atom"<<(i+1)<<"+PADDED_NUM_ATOMS*2], (mm_ulong) realToFixedPoint(force"<<(i+1)<<".z));\n";
        s<<"    MEM_FENCE;\n";
    }
    s<<"}\n";
    return s.str();
}

void BondedUtilities::computeInteractions(const std::vector<int>& groups) {
    // Equivalent to the original "if ((groups&allGroups) == 0) return;".
    // It must also return when allGroups is empty, i.e. when the context contains
    // no bonded forces at all, since then the kernel has not been initialized.
    bool anyIncluded = false;
    int min = std::min<int>(groups.size(), allGroups.size());
    for (int i = 0; i < min; i++) {
        if ((groups[i]&allGroups[i]) != 0) {
            anyIncluded = true;
            break;
        }
    }
    if (!anyIncluded)
        return;
    if (!hasInitializedKernels) {
        hasInitializedKernels = true;
        kernel->addArg(context.getLongForceBuffer());
        kernel->addArg(context.getEnergyBuffer());
        kernel->addArg(context.getPosq());
        for (int i = 0; i < 6; i++)
            kernel->addArg();
        for (int i = 0; i < (int) atomIndices.size(); i++)
            for (int j = 0; j < (int) atomIndices[i].size(); j++)
                kernel->addArg(atomIndices[i][j]);
        for (int i = 0; i < (int) arguments.size(); i++)
            kernel->addArg(*arguments[i]);
        if (energyParameterDerivatives.size() > 0)
            kernel->addArg(context.getEnergyParamDerivBuffer());
    }
    if (!hasInteractions)
        return;
    // Copy groups and insert the size of groups to first position.
    std::vector<int> copyGroups = groups;
    copyGroups.insert(copyGroups.begin(), copyGroups.size());
    // Create a ComputeArray object to store copyGroups (vector<int>).
    ComputeArray groupsBuffer;
    groupsBuffer.initialize(context, copyGroups.size(), sizeof(int), "groupsBuffer");
    // Copy the values in copyGroups (vector<int>) to the device memory.
    groupsBuffer.upload(copyGroups);
    kernel->setArg(3, groupsBuffer.getArray());
    Vec3 a, b, c;
    context.getPeriodicBoxVectors(a, b, c);
    if (context.getUseDoublePrecision()) {
        kernel->setArg(4, mm_double4(a[0], b[1], c[2], 0.0));
        kernel->setArg(5, mm_double4(1.0/a[0], 1.0/b[1], 1.0/c[2], 0.0));
        kernel->setArg(6, mm_double4(a[0], a[1], a[2], 0.0));
        kernel->setArg(7, mm_double4(b[0], b[1], b[2], 0.0));
        kernel->setArg(8, mm_double4(c[0], c[1], c[2], 0.0));
    }
    else {
        kernel->setArg(4, mm_float4((float) a[0], (float) b[1], (float) c[2], 0.0f));
        kernel->setArg(5, mm_float4(1.0f/(float) a[0], 1.0f/(float) b[1], 1.0f/(float) c[2], 0.0f));
        kernel->setArg(6, mm_float4((float) a[0], (float) a[1], (float) a[2], 0.0f));
        kernel->setArg(7, mm_float4((float) b[0], (float) b[1], (float) b[2], 0.0f));
        kernel->setArg(8, mm_float4((float) c[0], (float) c[1], (float) c[2], 0.0f));
    }
    kernel->execute(maxBonds);
}
