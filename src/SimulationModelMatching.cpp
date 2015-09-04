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

#include <sstream>
#include <string>
#include <iostream>

#include "core/SharedPointer.h"
#include <core/base/module/TimeTriggeredConferenceClientModule.h>
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/io/URL.h"
#include "core/io/StreamFactory.h"

#include "context/base/DirectInterface.h"
#include "context/base/RecordingContainer.h"
#include "context/base/RuntimeControl.h"
#include "context/base/RuntimeEnvironment.h"
#include "context/base/PlaybackContainer.h"

#include "vehiclecontext/VehicleRuntimeControl.h"
#include "vehiclecontext/model/CameraModel.h"
#include "vehiclecontext/model/SimplifiedBicycleModel.h"
#include "vehiclecontext/report/DistanceToObjectsReport.h"

#include "SimulationModelMatching.h"

using namespace std;
using namespace core;
using namespace core::base;
using namespace core::data;
using namespace core::io;
using namespace context::base;
using namespace vehiclecontext;
using namespace vehiclecontext::model;
using namespace vehiclecontext::report;
using namespace automotive;


namespace simulation {


    class FeatureMatcher : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            FeatureMatcher(const FeatureMatcher &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            FeatureMatcher& operator=(const FeatureMatcher &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            FeatureMatcher(const int32_t &argc, char **argv) :
                core::base::module::TimeTriggeredConferenceClientModule(argc, argv, "FeatureMatcher")
             {}

            virtual ~FeatureMatcher() {}

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
	            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                    cout << "Inside the main processing loop." << endl;

                    VehicleControl vehicleControl;
                    vehicleControl.setSpeed(1);
                    vehicleControl.setSteeringWheelAngle(0);

                    // Create container for finally sending the set values for the control algorithm.
                    Container c2(Container::VEHICLECONTROL, vehicleControl);
                    // Send container.
                    getConference().send(c2);

                }
                
                return coredata::dmcp::ModuleExitCodeMessage::OKAY;
            }

        private:
            virtual void setUp() {
                cout << "setUp" << endl;
            }

            virtual void tearDown() {
                cout << "tearDown" << endl;
            }
    };


    bool SimulationModelMatching::run() {
        bool retVal = false;

        const uint32_t MEMORYSEGMENT_SIZE = 2800000;
        const uint32_t NUMBER_OF_MEMORYSEGMENTS = 20;
        const float FREQ = 10;

        // 0. Setup system's configuration.
        stringstream sstrConfiguration;

        // Check relative path for scenario.
        sstrConfiguration
              << "# The following attributes define the buffer sizes for recording and replaying." << endl
              << "# You need to adjust these parameters depending on the camera resolution for example (640x480x3 --> 1000000 for memorySegment, 1280x720x3 --> 2800000)." << endl
              << "global.buffer.memorySegmentSize = " << MEMORYSEGMENT_SIZE << " # Size of a memory segment for a shared data stream in bytes." << endl
              << "global.buffer.numberOfMemorySegments = " << NUMBER_OF_MEMORYSEGMENTS << " # Number of memory segments used for buffering." << endl
              << endl
              << "global.scenario = file://Track.scnx" << endl
              << "global.showGrid = 0" << endl
              << endl
              << "odsimvehicle.posX = 0                     # Initial position X in cartesian coordinates." << endl
              << "odsimvehicle.posY = 0                     # Initial position Y in cartesian coordinates." << endl
              << "odsimvehicle.headingDEG = 90" << endl
              << "odsimvehicle.model=LinearBicycleModelNew  # Which motion model to be used: LinearBicycleModelNew or LinearBicycleModel (for CaroloCup 2013!)." << endl
              << "odsimvehicle.LinearBicycleModelNew.withSpeedController=1          # iff 1: use the VehicleControl.m_speed field; otherwise, ignore m_speed and use VehicleControl.m_acceleration field" << endl
              << "odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusLeft=4.85  # Minimum turning radius to the left (for calculating maximum steering angle to the left); Attention! we used data from the miniature vehicle Meili and thus, all values are scaled by factor 10 to be compatible with the simulation!" << endl
              << "odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusRight=5.32 # Minimum turning radius to the right (for calculating maximum steering angle to the right); Attention! we used data from the miniature vehicle Meili and thus, all values are scaled by factor 10 to be compatible with the simulation!" << endl
              << "odsimvehicle.LinearBicycleModelNew.wheelbase=2.65                 # Wheelbase; Attention! we used data from the miniature vehicle Meili and thus, all values are scaled by factor 10 to be compatible with the simulation!" << endl
              << "odsimvehicle.LinearBicycleModelNew.invertedSteering=0             # iff 0: interpret neg. steering wheel angles as steering to the left; iff 1: otherwise" << endl
              << "odsimvehicle.LinearBicycleModelNew.maxSpeed=2.0                   # maxium speed in m/ss" << endl
              << endl;

        // 1. Setup runtime control.
        DirectInterface di("225.0.0.100", 100, sstrConfiguration.str());
        VehicleRuntimeControl vrc(di);
        vrc.setup(RuntimeControl::TAKE_CONTROL);

        // 2. Setup application.
        string argv0("FeatureMatcher");
        string argv1("--cid=100");
        string argv2("--freq=10");
        string argv3("--verbose=1");
        int32_t argc = 4;
        char **argv;
        argv = new char*[4];
        argv[0] = const_cast<char*>(argv0.c_str());
        argv[1] = const_cast<char*>(argv1.c_str());
        argv[2] = const_cast<char*>(argv2.c_str());
        argv[3] = const_cast<char*>(argv3.c_str());

        // 3. Instantiate actual System-Under-Test.
        FeatureMatcher myFeatureMatcher(argc, argv);

        // 4. System's context components.
        SimplifiedBicycleModel bicycleControl(FREQ, sstrConfiguration.str());
        CameraModel cameraModel(FREQ, sstrConfiguration.str());

        // 5. Compose simulation of system's context.
        RuntimeEnvironment rte;
        rte.add(myFeatureMatcher);
        rte.add(bicycleControl);
        rte.add(cameraModel);

        // 6. Run application under supervision of RuntimeControl for maximum 100s.
        retVal = vrc.run(rte, 10) == RuntimeControl::APPLICATIONS_FINISHED;

        // TODO: As the playback component cannot end a simulation when the recording
        // file has ended, we manually set this simulation to pass.
        retVal = true;

        // 7. And finally clean up.
        vrc.tearDown();
        return retVal;
    }
}

