/**
 * simulation-model-matching - Experiment to study matching
 *                             recordings from the real world
 *                             with simulation data to extract
 *                             matching feature sets.
 * Copyright (C) 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SIMULATIONMODELMATCHING_H_
#define SIMULATIONMODELMATCHING_H_

#include "core/platform.h"

namespace simulation {
    class SimulationModelMatching {
        public:
            /**
             * This method executes the simulation and returns true
             * if everything ran as expected.
             *
             * @return true if everything ran as expected.
             */
            bool run();
    };
}

#endif // SIMULATIONMODELMATCHING_H_
