/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit.                   *
 * See https://openmm.org/development.                                        *
 *                                                                            *
 * Tests for the multi-topology force group support (force groups >= 32), the *
 * external force driven oneStep() integrator API, the step count accessors    *
 * and the direct Context data accessors.                                     *
 * (Added for the QCDyn modified OpenMM.)                                     *
 * -------------------------------------------------------------------------- */

#include "openmm/internal/AssertionUtilities.h"
#include "openmm/Context.h"
#include "openmm/CustomExternalForce.h"
#include "openmm/Platform.h"
#include "openmm/State.h"
#include "openmm/System.h"
#include "openmm/VerletIntegrator.h"
#include <iostream>
#include <vector>

using namespace OpenMM;
using namespace std;

/**
 * Build a one particle system with two harmonic traps: one in the first
 * topology (force group 0) and one in the second topology (force group 32).
 */
static System buildSystem() {
    System system;
    system.addParticle(1.0);
    CustomExternalForce* f0 = new CustomExternalForce("0.5*k*x^2");
    f0->addGlobalParameter("k", 1.0);
    f0->addParticle(0);
    f0->setForceGroup(0);
    system.addForce(f0);
    CustomExternalForce* f1 = new CustomExternalForce("0.5*k*y^2");
    f1->addGlobalParameter("k", 1.0);
    f1->addParticle(0);
    f1->setForceGroup(32); // second topology, bit 0
    system.addForce(f1);
    return system;
}

void testLayeredForceGroups() {
    System system = buildSystem();
    // Force groups beyond 31 must be accepted.
    ASSERT_EQUAL(system.getForce(1).getForceGroup(), 32);
    VerletIntegrator integrator(0.001);
    Context context(system, integrator, Platform::getPlatformByName("Reference"));
    vector<Vec3> positions(1, Vec3(1.0, 2.0, 0.0));
    context.setPositions(positions);

    // The default only includes the first topology: 0.5*x^2 = 0.5.
    double defaultEnergy = context.getState(State::Energy).getPotentialEnergy();
    ASSERT_EQUAL_TOL(0.5, defaultEnergy, 1e-9);

    // Explicitly requesting both topologies includes the second trap: 0.5 + 0.5*4 = 2.5.
    vector<int> both(2, -1);
    double bothEnergy = context.getState(State::Energy, false, both).getPotentialEnergy();
    ASSERT_EQUAL_TOL(2.5, bothEnergy, 1e-9);

    // Selecting only the second topology gives 0.5*4 = 2.0.
    vector<int> onlySecond;
    onlySecond.push_back(0);
    onlySecond.push_back(1);
    double secondEnergy = context.getState(State::Energy, false, onlySecond).getPotentialEnergy();
    ASSERT_EQUAL_TOL(2.0, secondEnergy, 1e-9);

    // Same through the direct Context accessor.
    ASSERT_EQUAL_TOL(2.5, context.getPotentialEnergy(true, both), 1e-9);
}

void testStepCount() {
    System system = buildSystem();
    VerletIntegrator integrator(0.001);
    Context context(system, integrator, Platform::getPlatformByName("Reference"));
    context.setStep(1234);
    ASSERT_EQUAL(1234, context.getStep());
}

void testDirectAccess() {
    System system = buildSystem();
    VerletIntegrator integrator(0.001);
    Context context(system, integrator, Platform::getPlatformByName("Reference"));
    vector<Vec3> positions(1, Vec3(1.0, 2.0, 0.0));
    context.setPositions(positions);
    vector<Vec3> readPositions, readForces;
    context.getPositions(readPositions);
    ASSERT_EQUAL(1, readPositions.size());
    ASSERT_EQUAL_TOL(1.0, readPositions[0][0], 1e-9);
    ASSERT_EQUAL_TOL(2.0, readPositions[0][1], 1e-9);
    // Forces are only populated once a force evaluation has been requested.
    context.getState(State::Forces);
    context.getForces(readForces);
    ASSERT_EQUAL(1, readForces.size());
    // Only the first topology contributes by default: Fx = -k*x = -1, Fy = 0.
    ASSERT_EQUAL_TOL(-1.0, readForces[0][0], 1e-9);
    ASSERT_EQUAL_TOL(0.0, readForces[0][1], 1e-9);
}

void testOneStepWithExternalForces() {
    System system = buildSystem();
    VerletIntegrator integrator(0.001);
    Context context(system, integrator, Platform::getPlatformByName("Reference"));
    vector<Vec3> positions(1, Vec3(1.0, 2.0, 0.0));
    context.setPositions(positions);
    context.setVelocities(vector<Vec3>(1, Vec3(0.0, 0.0, 0.0)));

    // Apply an external force of -10 along x.  After one step of size 0.001 with
    // a unit mass the x velocity must be -0.01, regardless of the internal forces.
    vector<Vec3> externalForces(1, Vec3(-10.0, 0.0, 0.0));
    integrator.oneStep(externalForces);
    vector<Vec3> velocities;
    context.getVelocities(velocities);
    ASSERT_EQUAL_TOL(-0.01, velocities[0][0], 1e-12);
}

int main(int argc, char* argv[]) {
    try {
        testLayeredForceGroups();
        testStepCount();
        testDirectAccess();
        testOneStepWithExternalForces();
    }
    catch(const exception& e) {
        cout << "exception: " << e.what() << endl;
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}
