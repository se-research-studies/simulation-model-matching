#include "abstractparticipant.h"

namespace SimulationGame {

    AbstractParticipant::AbstractParticipant(int argc, char** argv, const std::string& name)
        : odcore::base::module::TimeTriggeredConferenceClientModule(argc, argv, name)
    {
    }

    AbstractParticipant::~AbstractParticipant()
    {
    }

    void AbstractParticipant::setUp()
    {
        //        // Initialize fonts.
        //        const double hscale = 0.4;
        //        const double vscale = 0.3;
        //        const double shear = 0.2;
        //        const int thickness = 1;
        //        const int lineType = 6;

        //        cvInitFont(&m_font, CV_FONT_HERSHEY_DUPLEX, hscale, vscale, shear, thickness, lineType);
    }

    void AbstractParticipant::tearDown()
    {

    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::body()
    {
        // Code from LaneFollower.cpp

//        // Get configuration data.
//        KeyValueConfiguration kv = getKeyValueConfiguration();
//        m_debug = kv.getValue<int32_t> ("lanefollower.debug") == 1;

//        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
//                        bool has_next_frame = false;

//                        // Get the most recent available container for a SharedImage.
//                        Container c = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());

//                        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
//                            // Example for processing the received container.
//                            has_next_frame = readSharedImage(c);
//                        }

//                        // Process the read image and calculate regular lane following set values for control algorithm.
//                        if (true == has_next_frame) {
//                            processImage();
//                        }
//                        Container c2(m_vehicleControl);
//                        // Send container.
//                        getConference().send(c2);
//        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

    bool AbstractParticipant::readSharedImage(odcore::data::Container& container)
    {
        // Code from LaneFollower.cpp:

        bool retVal = false;

//        if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
//            SharedImage si = container.getData<SharedImage> ();

//            // Check if we have already attached to the shared memory.
//            if (!m_hasAttachedToSharedImageMemory) {
//                m_sharedImageMemory
//                        = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(
//                                si.getName());
//            }

//            // Check if we could successfully attach to the shared memory.
//            if (m_sharedImageMemory->isValid()) {
//                // Lock the memory region to gain exclusive access using a scoped lock.
//                Lock l(m_sharedImageMemory);
//                const uint32_t numberOfChannels = 3;
//                // For example, simply show the image.
//                if (m_image == NULL) {
//                    m_image = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, numberOfChannels);
//                }

//                // Copying the image data is very expensive...
//                if (m_image != NULL) {
//                    memcpy(m_image->imageData,
//                           m_sharedImageMemory->getSharedMemory(),
//                           si.getWidth() * si.getHeight() * numberOfChannels);
//                }

//                // Mirror the image.
//                cvFlip(m_image, 0, -1);

//                retVal = true;
//            }
//        }
        return retVal;
    }


} // namespace SimulationGame
