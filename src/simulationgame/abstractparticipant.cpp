#include "abstractparticipant.h"

#include <iostream>

#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include <opendavinci/odcore/base/Lock.h>

namespace SimulationGame {

    AbstractParticipant::AbstractParticipant(int argc, char** argv, const std::string& name)
        : odcore::base::module::TimeTriggeredConferenceClientModule(argc, argv, name)
    {
    }

    AbstractParticipant::~AbstractParticipant()
    {
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::runModule(uint32_t frameLimit, const std::string& featureSource)
    {
        this->frameLimit = frameLimit;
        if (featureSource.size() > 0) {
            featureSet = featureSetDao.load(featureSource);
        }
        return odcore::base::module::TimeTriggeredConferenceClientModule::runModule();
    }

    void AbstractParticipant::setUp()
    {
    }

    void AbstractParticipant::tearDown()
    {

    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::body()
    {
        uint32_t frame = 0;
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING && frame < frameLimit) {
            ++frame;
            odcore::data::Container container = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());
            if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
                odcore::data::image::SharedImage sharedImage = container.getData<odcore::data::image::SharedImage>();
                std::shared_ptr<odcore::wrapper::SharedMemory> sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());
                if (sharedImageMemory->isValid()) {
                    odcore::base::Lock l(sharedImageMemory);
                    cv::Mat image(cv::Size(sharedImage.getWidth(), sharedImage.getHeight()), CV_MAKETYPE(CV_8U, sharedImage.getBytesPerPixel()), sharedImageMemory->getSharedMemory());
                    cv::flip(image, image, -1);
                    addFeatures(image, frame);
                    processImage(image);
                    cv::imshow("Image", image);
                    cv::waitKey(10);
                }
            } else {
                std::cout << "Container does not contain image" << std::endl;
            }
        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

    void AbstractParticipant::setControls(double speed, double steeringWheelAngle)
    {
        if (steeringWheelAngle != lastSteeringWheelAngle) {
            // add steering action;
        }
        lastSteeringWheelAngle = steeringWheelAngle;
        if (speed != lastSpeed) {
            // add speed change
        }
        lastSpeed = speed;
        vehicleControl.setSpeed(speed);
        vehicleControl.setSteeringWheelAngle(steeringWheelAngle);
        odcore::data::Container container(vehicleControl);
        getConference().send(container);
    }

    void AbstractParticipant::addFeatures(cv::Mat& image, uint32_t frame) const
    {
        if (featureSet != nullptr) {
            const Common::DirtyFrame& dirtyFrame = featureSet->getFrame(frame % featureSet->getFrameCount());
            for (const Common::Feature& feature : dirtyFrame.getFeatures()) {
                cv::circle(image, cv::Point(feature.getX(), feature.getY()), 5, cv::Scalar(255, 255, 255), -1);
            }
        }
    }

} // namespace SimulationGame
