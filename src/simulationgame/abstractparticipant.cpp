#include "abstractparticipant.h"

#include <iostream>

#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include <opendavinci/odcore/base/Lock.h>

namespace SimulationGame {

    AbstractParticipant::AbstractParticipant(int argc, char** argv, const std::string& name, uint32_t frameLimit)
        : odcore::base::module::TimeTriggeredConferenceClientModule(argc, argv, name), frameLimit(frameLimit)
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

        //        // Get configuration data.
        //        KeyValueConfiguration kv = getKeyValueConfiguration();
        //        m_debug = kv.getValue<int32_t> ("lanefollower.debug") == 1;
    }

    void AbstractParticipant::tearDown()
    {

    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::body()
    {
        uint32_t frame = 0;

        std::cout << "Entering body" << std::endl;
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING && frame < frameLimit) {
            ++frame;
            std::cout << "Still running" << std::endl;
            odcore::data::Container container = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());
            if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
                std::cout << "Got next image..." << std::endl;
                odcore::data::image::SharedImage sharedImage = container.getData<odcore::data::image::SharedImage>();
                std::shared_ptr<odcore::wrapper::SharedMemory> sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());
                if (sharedImageMemory->isValid()) {                    
                    std::cout << "Image read from memory" << std::endl;
                    odcore::base::Lock l(sharedImageMemory);
                    cv::Mat image(sharedImage.getWidth(), sharedImage.getHeight(), CV_MAKETYPE(CV_8U, sharedImage.getBytesPerPixel()), sharedImageMemory->getSharedMemory());
                    cv::flip(image, image, -1);
                    std::cout << "Processing image" << std::endl;
                    cv::imshow("Image", image);
                    cv::waitKey(/*50*/);
                    processImage(image);                    
                    std::cout << "Image processed" << std::endl;
                }
            } else {
                std::cout << "Container does not contain image" << std::endl;
            }
        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

    void AbstractParticipant::setControls(double speed, double steeringWheelAngle)
    {
        std::cout << "Setting speed " << speed << ", angle " << steeringWheelAngle << std::endl;
        vehicleControl.setSpeed(speed);
        vehicleControl.setSteeringWheelAngle(steeringWheelAngle);
        odcore::data::Container container(vehicleControl);
        getConference().send(container);
    }

} // namespace SimulationGame
