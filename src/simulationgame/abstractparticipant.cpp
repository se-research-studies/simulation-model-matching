#include "abstractparticipant.h"

#include <iostream>

#include <automotivedata/generated/automotive/VehicleData.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include <opendavinci/odcore/base/Lock.h>

#include <FeatureSimulation/Common/utils.h>

#include <FeatureSimulation/SimulationGame/settings.h>

namespace SimulationGame {

    AbstractParticipant::AbstractParticipant(int argc, char** argv, const std::string& name)
        : odcore::base::module::TimeTriggeredConferenceClientModule(argc, argv, name)
    {
    }

    AbstractParticipant::~AbstractParticipant()
    {
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::runModule(const Settings& settings, Common::LocalFeatureSets&& featureSets)
    {
        frameLimit = settings.frameLimit;
        showGui = settings.showGui;
        dataGatherer.setCorrelationFile(Common::Utils::fileName(settings.correlationFile));
        featureScale = settings.featureScale;
        featureSize = settings.featureSize;
        localFeatureSets = std::move(featureSets);
        return odcore::base::module::TimeTriggeredConferenceClientModule::runModule();
    }

    void AbstractParticipant::forceQuit()
    {
        quitFlag = true;
    }

    void AbstractParticipant::setUp()
    {
        std::string simulationName = getDMCPClient()->getConfiguration().getValue<std::string>("global.scenario");
        dataGatherer.setSimulationName(Common::Utils::fileName(simulationName));
        currentFrame = 0;
    }

    void AbstractParticipant::tearDown()
    {
        dataGatherer.save();
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::body()
    {
        gatherDataBeforeSimulation();
        while (continueBody()) {
            odcore::data::Container container = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());
            if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
                odcore::data::image::SharedImage sharedImage = container.getData<odcore::data::image::SharedImage>();
                processFrame(sharedImage);
            } else {
                std::cout << "Container does not contain image" << std::endl;
            }
        }
        gatherDataAfterSimulation();
        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

    bool AbstractParticipant::continueBody()
    {
        return getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING &&
                (frameLimit == 0 || currentFrame < frameLimit) &&
                !quitFlag;
    }

    void AbstractParticipant::processFrame(const odcore::data::image::SharedImage& sharedImage)
    {
        std::shared_ptr<odcore::wrapper::SharedMemory> sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());
        if (sharedImageMemory->isValid()) {
            ++currentFrame;
            cv::Mat image = prepareImage(sharedImage, sharedImageMemory);

            gatherDataBeforeFrame();
            processImage(image);
            gatherDataAfterFrame();

            if (showGui) {
                cv::imshow("Image", image);
                cv::waitKey(10);
            }
        }
    }

    cv::Mat AbstractParticipant::prepareImage(const odcore::data::image::SharedImage& sharedImage, const std::shared_ptr<odcore::wrapper::SharedMemory>& sharedImageMemory)
    {
        odcore::base::Lock l(sharedImageMemory);
        cv::Mat image(cv::Size(sharedImage.getWidth(), sharedImage.getHeight()), CV_MAKETYPE(CV_8U, sharedImage.getBytesPerPixel()), sharedImageMemory->getSharedMemory());
        cv::flip(image, image, -1);
        addFeatures(image);
        return image;
    }

    void AbstractParticipant::gatherDataBeforeSimulation()
    {
        dataGatherer.start();
    }

    void AbstractParticipant::gatherDataBeforeFrame()
    {
        dataGatherer.startFrame();
    }

    void AbstractParticipant::gatherDataDuringFrame(double speed, double steeringWheelAngle)
    {
        dataGatherer.midFrame(speed, steeringWheelAngle);
    }

    void AbstractParticipant::gatherDataAfterFrame()
    {
        dataGatherer.finishFrame();
    }

    void AbstractParticipant::gatherDataAfterSimulation()
    {
        dataGatherer.stop();
    }

    void AbstractParticipant::addFeatures(cv::Mat& image)
    {
        if (localFeatureSets.size() > 0) {
            odcore::data::Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
            automotive::VehicleData vd = containerVehicleData.getData<automotive::VehicleData>();
            cartesian::Point2 position = vd.getPosition();

            for (const auto& localFeatureSet : localFeatureSets) {
                const Common::Rectangle& segment = localFeatureSet.first;
                if (liesInRectangle(position, segment)) {
                    const std::unique_ptr<Common::FeatureSet>& featureSet = localFeatureSet.second;
                    if (lastSegment != segment) {
                        currentFrameInSegment = featureSet->getFirstFrame();
                        lastSegment = segment;
                    } else if (currentFrameInSegment > featureSet->getLastFrame()) {
                        currentFrameInSegment = featureSet->getFirstFrame();
                    } else {
                        ++currentFrameInSegment;
                    }
                    const Common::DirtyFrame& dirtyFrame = featureSet->getFrame(currentFrameInSegment);
                    addFeaturesFromFrame(image, dirtyFrame);
                    break;
                }
            }
        }
    }

    bool AbstractParticipant::liesInRectangle(cartesian::Point2& point, const Common::Rectangle& rectangle) const
    {
        int x = Common::Utils::to<int>(point.getP()[0]);
        int y = Common::Utils::to<int>(point.getP()[1]);
        return rectangle.getTopLeft().getX() < x && rectangle.getTopLeft().getY() < y &&
                rectangle.getBottomRight().getX() > x && rectangle.getBottomRight().getY() > y;
    }

    void AbstractParticipant::addFeaturesFromFrame(cv::Mat& image, const Common::DirtyFrame& dirtyFrame) const
    {
        for (const Common::Feature& feature : dirtyFrame.getFeatures()) {
            int radius = featureSize > 0 ? featureSize : Common::Utils::to<int>((feature.getDiameter() / 2) * featureScale);
            cv::circle(image, cv::Point(feature.getX(), feature.getY()), radius, cv::Scalar(255, 255, 255), -1);
        }
    }

    void AbstractParticipant::setControls(double speed, double steeringWheelAngle)
    {
        gatherDataDuringFrame(speed, steeringWheelAngle);
        vehicleControl.setSpeed(speed);
        vehicleControl.setSteeringWheelAngle(steeringWheelAngle);
        odcore::data::Container container(vehicleControl);
        getConference().send(container);
    }

} // namespace SimulationGame
