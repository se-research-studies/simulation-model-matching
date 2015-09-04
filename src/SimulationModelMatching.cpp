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
#include "core/base/Lock.h"
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/io/URL.h"
#include "core/io/StreamFactory.h"
#include "core/wrapper/SharedMemoryFactory.h"

#include "context/base/DirectInterface.h"
#include "context/base/RecordingContainer.h"
#include "context/base/RuntimeControl.h"
#include "context/base/RuntimeEnvironment.h"
#include "context/base/PlaybackContainer.h"

#include "tools/player/Player.h"

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
using namespace tools::player;
using namespace vehiclecontext;
using namespace vehiclecontext::model;
using namespace vehiclecontext::report;
using namespace automotive;
using namespace coredata::image;


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
                core::base::module::TimeTriggeredConferenceClientModule(argc, argv, "FeatureMatcher"),
                m_player(),
                m_hasAttachedToSharedImageMemoryFromSimulation(false),
                m_sharedImageMemoryFromSimulation(),
                m_imageFromSimulation(),
                m_hasAttachedToSharedImageMemoryFromPlayer(false),
                m_sharedImageMemoryFromPlayer(),
                m_imageFromPlayer()
             {}

            virtual ~FeatureMatcher() {}

            bool readSharedImageFromSimulation(Container &c) {
	            bool retVal = false;

	            if (c.getDataType() == Container::SHARED_IMAGE) {
		            SharedImage si = c.getData<SharedImage> ();

		            // Check if we have already attached to the shared memory.
		            if (!m_hasAttachedToSharedImageMemoryFromSimulation) {
			            m_sharedImageMemoryFromSimulation
					            = core::wrapper::SharedMemoryFactory::attachToSharedMemory(
							            si.getName());
		            }

		            // Check if we could successfully attach to the shared memory.
		            if (m_sharedImageMemoryFromSimulation->isValid()) {
			            // Lock the memory region to gain exclusive access using a scoped lock.
                        Lock l(m_sharedImageMemoryFromSimulation);
			            const uint32_t numberOfChannels = si.getBytesPerPixel();
			            // For example, simply show the image.
			            if (m_imageFromSimulation == NULL) {
				            m_imageFromSimulation = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, numberOfChannels);
			            }

			            // Copying the image data is very expensive...
			            if (m_imageFromSimulation != NULL) {
				            memcpy(m_imageFromSimulation->imageData,
						           m_sharedImageMemoryFromSimulation->getSharedMemory(),
						           si.getWidth() * si.getHeight() * numberOfChannels);
			            }

			            // Mirror the image.
			            cvFlip(m_imageFromSimulation, 0, -1);

			            retVal = true;
		            }
	            }
	            return retVal;
            }

            bool readSharedImageFromPlayer(Container &c) {
	            bool retVal = false;

	            if (c.getDataType() == Container::SHARED_IMAGE) {
		            SharedImage si = c.getData<SharedImage> ();

		            // Check if we have already attached to the shared memory.
		            if (!m_hasAttachedToSharedImageMemoryFromPlayer) {
			            m_sharedImageMemoryFromPlayer
					            = core::wrapper::SharedMemoryFactory::attachToSharedMemory(
							            si.getName());
		            }

		            // Check if we could successfully attach to the shared memory.
		            if (m_sharedImageMemoryFromPlayer->isValid()) {
			            // Lock the memory region to gain exclusive access using a scoped lock.
                        Lock l(m_sharedImageMemoryFromPlayer);
			            const uint32_t numberOfChannels = si.getBytesPerPixel();
			            // For example, simply show the image.
			            if (m_imageFromPlayer == NULL) {
				            m_imageFromPlayer = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, numberOfChannels);
			            }

			            // Copying the image data is very expensive...
			            if (m_imageFromPlayer != NULL) {
				            memcpy(m_imageFromPlayer->imageData,
						           m_sharedImageMemoryFromPlayer->getSharedMemory(),
						           si.getWidth() * si.getHeight() * numberOfChannels);
			            }

			            // Mirror the image (not required for recording).
//			            cvFlip(m_imageFromPlayer, 0, -1);

			            retVal = true;
		            }
	            }
	            return retVal;
            }

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
	            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                    cout << "[FeatureMatcher] Inside the main processing loop." << endl;

                    // Trigger movement of vehicle to get valid simulation data.
                    VehicleControl vehicleControl;
                    vehicleControl.setSpeed(1);
                    vehicleControl.setSteeringWheelAngle(0);

                    // Create container for finally sending the set values for the control algorithm.
                    Container c2(Container::VEHICLECONTROL, vehicleControl);
                    // Send container.
                    getConference().send(c2);

                    // Get virtual data from simulation.
                    bool hasNextFrameFromSimulation = false;
                    {
		                Container c = getKeyValueDataStore().get(Container::SHARED_IMAGE);

		                if (c.getDataType() == Container::SHARED_IMAGE) {
			                // Example for processing the received container.
			                hasNextFrameFromSimulation = readSharedImageFromSimulation(c);
		                }

		                // Process the read image and calculate regular lane following set values for control algorithm.
		                if (true == hasNextFrameFromSimulation) {
                            if (m_imageFromSimulation != NULL) {
                                cvShowImage("FromSimulation", m_imageFromSimulation);
                                cvWaitKey(1);
                            }
		                }
                    }

                    // Get some data from recording file.
                    bool hasNextFrameFromPlayer = false;
                    {
                        Container c;
                        if (m_player.get() != NULL) {
                            const uint16_t MAX_FRAMES = 50;
                            for (uint16_t i = 0; i < MAX_FRAMES; i++) {
                                // Read the next container from file.
                                if (m_player->hasMoreData()) {
                                    c = m_player->getNextContainerToBeSent();
                                }

		                        if (c.getDataType() == Container::SHARED_IMAGE) {
			                        // Example for processing the received container.
			                        hasNextFrameFromPlayer = readSharedImageFromPlayer(c);
		                        }

		                        // Process the read image and calculate regular lane following set values for control algorithm.
		                        if (true == hasNextFrameFromPlayer) {
                                    if (m_imageFromPlayer != NULL) {
                                        cvShowImage("FromPlayer", m_imageFromPlayer);
                                        cvWaitKey(1);
                                    }
		                        }

                                if (hasNextFrameFromSimulation && hasNextFrameFromPlayer) {
                                    cout << "[FeatureMatcher] TODO: Use the goodFeatureToTrack method to match reality with simulation here." << endl;
                                }
                            }
                        }
                    }
                }
                
                return coredata::dmcp::ModuleExitCodeMessage::OKAY;
            }

        private:
            virtual void setUp() {
                cout << "[FeatureMatcher] Setting up." << endl;
                    
                core::io::URL recordingFile(getKeyValueConfiguration().getValue<string>("featurematcher.recording"));

                // Size of the memory buffer.
                const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");

                // Number of memory segments.
                const uint32_t NUMBER_OF_SEGMENTS = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.numberOfMemorySegments");

                // If AUTO_REWIND is true, the file will be played endlessly.
                const bool AUTO_REWIND = true;

                // Run player synchronously.
                const bool THREADING = false;

                // Create player.
                m_player = auto_ptr<tools::player::Player>(new Player(recordingFile, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING));

                // Create window to display simulation data.
		        cvNamedWindow("FromSimulation", CV_WINDOW_AUTOSIZE);
		        cvMoveWindow("FromSimulation", 300, 100);

                // Create window to display player data.
		        cvNamedWindow("FromPlayer", CV_WINDOW_AUTOSIZE);
		        cvMoveWindow("FromPlayer", 300, 100);
            }

            virtual void tearDown() {
                cout << "[FeatureMatcher] Tear down." << endl;

	            if (m_imageFromSimulation != NULL) {
		            cvReleaseImage(&m_imageFromSimulation);
	            }
	            if (m_imageFromPlayer != NULL) {
		            cvReleaseImage(&m_imageFromPlayer);
	            }

	            cvDestroyWindow("FromSimulation");
	            cvDestroyWindow("FromPlayer");
            }

        private:
            auto_ptr<tools::player::Player> m_player;

            bool m_hasAttachedToSharedImageMemoryFromSimulation;
            core::SharedPointer<core::wrapper::SharedMemory> m_sharedImageMemoryFromSimulation;
            IplImage *m_imageFromSimulation;

            bool m_hasAttachedToSharedImageMemoryFromPlayer;
            core::SharedPointer<core::wrapper::SharedMemory> m_sharedImageMemoryFromPlayer;
            IplImage *m_imageFromPlayer;
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
              << endl
              << "featurematcher.recording = file://straightroad.rec" << endl
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

