#ifndef OPENMM_FORCEGROUPSSERIALIZER_H_
#define OPENMM_FORCEGROUPSSERIALIZER_H_

/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit.                   *
 * See https://openmm.org/development.                                        *
 *                                                                            *
 * Portions copyright (c) 2008-2024 Stanford University and the Authors.      *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "openmm/serialization/SerializationNode.h"
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>

namespace OpenMM {

/**
 * Helpers for serializing the vector of force group flags used by Integrators.
 * (Added by zhubin for the multi-topology force group support.)
 *
 * A single group mask is written as an int property so that files written by
 * older versions of OpenMM remain byte identical and fully compatible.  When
 * there are multiple topologies the masks are written as a comma separated
 * string, for example "integrationForceGroups=\"-1,-1\"".
 */

/**
 * Store a force group vector into a SerializationNode.
 */
inline void setForceGroupsProperty(SerializationNode& node, const std::string& name, const std::vector<int>& groups) {
    if (groups.size() <= 1)
        node.setIntProperty(name, (groups.size() == 0 ? -1 : groups[0]));
    else {
        std::stringstream value;
        for (int i = 0; i < (int) groups.size(); i++) {
            if (i > 0)
                value << ",";
            value << groups[i];
        }
        node.setStringProperty(name, value.str());
    }
}

/**
 * Load a force group vector from a SerializationNode.  Both the legacy single
 * int representation and the comma separated multi-topology representation
 * are accepted.
 */
inline std::vector<int> getForceGroupsProperty(const SerializationNode& node, const std::string& name, int defaultValue) {
    std::stringstream defaultText;
    defaultText << defaultValue;
    std::string text = node.getStringProperty(name, defaultText.str());
    std::vector<int> groups;
    std::stringstream input(text);
    std::string item;
    while (std::getline(input, item, ',')) {
        const char* start = item.c_str();
        char* end = NULL;
        long value = std::strtol(start, &end, 10);
        if (end != start)
            groups.push_back((int) value);
    }
    if (groups.size() == 0)
        groups.push_back(defaultValue);
    return groups;
}

} // namespace OpenMM

#endif /*OPENMM_FORCEGROUPSSERIALIZER_H_*/
