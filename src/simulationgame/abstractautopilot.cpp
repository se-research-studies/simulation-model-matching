#include "abstractautopilot.h"

#include <iostream>

#include <automotivedata/generated/automotive/VehicleData.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include <opendavinci/odcore/base/Lock.h>

#include <FeatureSimulation/Common/utils.h>

#include <FeatureSimulation/SimulationGame/settings.h>

namespace SimulationGame {

    AbstractAutopilot::AbstractAutopilot(int argc, char** argv, const std::string& name)
        : odcore::base::module::TimeTriggeredConferenceClientModule(argc, argv, name) {
    }

    AbstractAutopilot::~AbstractAutopilot() {
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractAutopilot::runModule(const Settings& settings, Common::Permutation&& permutation) {
        frameLimit = settings.frameLimit;
        showGui = settings.showGui;
        dataGatherer.setCorrelationFile(Common::Utils::fileName(settings.correlationFile));
        dataGatherer.setId(settings.id);
        dataGatherer.setPermutationIndex(permutation.index);
        featureScale = settings.featureScale;
        featureSize = settings.featureSize;
        localFeatureSets = std::move(permutation.localFeatureSets);
        return odcore::base::module::TimeTriggeredConferenceClientModule::runModule();
    }

    void AbstractAutopilot::forceQuit() {
        quitFlag = true;
    }

    void AbstractAutopilot::setUp() {
        std::string simulationName = getDMCPClient()->getConfiguration().getValue<std::string>("global.scenario");
        dataGatherer.setSimulationName(Common::Utils::fileName(simulationName));
        currentFrame = 0;
    }

    void AbstractAutopilot::tearDown() {
        dataGatherer.save();
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractAutopilot::body() {
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

    bool AbstractAutopilot::continueBody() {
        return getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING &&
                (frameLimit == 0 || currentFrame < frameLimit) &&
                !quitFlag;
    }

    void AbstractAutopilot::processFrame(const odcore::data::image::SharedImage& sharedImage) {
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

    cv::Mat AbstractAutopilot::prepareImage(const odcore::data::image::SharedImage& sharedImage, const std::shared_ptr<odcore::wrapper::SharedMemory>& sharedImageMemory) {
        odcore::base::Lock l(sharedImageMemory);
        cv::Mat image(cv::Size(Common::Utils::to<int>(sharedImage.getWidth()),Common::Utils::to<int>(sharedImage.getHeight())),
                      Common::Utils::to<int>(CV_MAKETYPE(CV_8U, sharedImage.getBytesPerPixel())),
                      sharedImageMemory->getSharedMemory());
        // The image has to be flipped horizontally and vertically. OpenGl seems to create a flipped image.
        cv::flip(image, image, -1);
        addFeatures(image);
        return image;
    }

    void AbstractAutopilot::gatherDataBeforeSimulation() {
        dataGatherer.start();
    }

    void AbstractAutopilot::gatherDataBeforeFrame() {
        dataGatherer.startFrame();
    }

    void AbstractAutopilot::gatherDataDuringFrame(double speed, double steeringWheelAngle) {
        dataGatherer.midFrame(speed, steeringWheelAngle);
    }

    void AbstractAutopilot::gatherDataAfterFrame() {
        dataGatherer.finishFrame();
    }

    void AbstractAutopilot::gatherDataAfterSimulation() {
        dataGatherer.stop();
    }

    void AbstractAutopilot::addFeatures(cv::Mat& image) {
        if (localFeatureSets.size() > 0) {
            odcore::data::Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
            automotive::VehicleData vd = containerVehicleData.getData<automotive::VehicleData>();
            cartesian::Point2 position = vd.getPosition();

            // Iterates over all the feature sets until we find the simulation segment the car is in.
            // Then the features for that segment are added to the image
            for (const auto& localFeatureSet : localFeatureSets) {
                const Common::Rectangle& segment = localFeatureSet.first;
                if (liesInRectangle(position, segment)) {
                    const std::unique_ptr<Common::FeatureSet>& featureSet = localFeatureSet.second;
                    if (lastSegment != segment) {
                        // The car is in a new segment, so the frame for the current segment has to be reset
                        currentFrameInSegment = featureSet->getFirstFrame();
                        lastSegment = segment;
                    } else if (currentFrameInSegment == featureSet->getLastFrame()) {
                        // The car is still in the last segment, but has reached the last frame of the feature set, so we start again at the first
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

    bool AbstractAutopilot::liesInRectangle(cartesian::Point2& point, const Common::Rectangle& rectangle) const {
        int x = Common::Utils::to<int>(point.getP()[0]);
        int y = Common::Utils::to<int>(point.getP()[1]);
        return rectangle.getTopLeft().getX() < x && rectangle.getTopLeft().getY() < y &&
                rectangle.getBottomRight().getX() > x && rectangle.getBottomRight().getY() > y;
    }

    void AbstractAutopilot::addFeaturesFromFrame(cv::Mat& image, const Common::DirtyFrame& dirtyFrame) const {
        for (const Common::Feature& feature : dirtyFrame.getFeatures()) {
            int radius = featureSize > 0 ? featureSize : Common::Utils::to<int>((feature.getDiameter() / 2) * featureScale);
            cv::circle(image, cv::Point(feature.getX(), feature.getY()), radius, cv::Scalar(255, 255, 255), -1);
        }
    }

    void AbstractAutopilot::setControls(double speed, double steeringWheelAngle) {
        gatherDataDuringFrame(speed, steeringWheelAngle);
        vehicleControl.setSpeed(speed);
        vehicleControl.setSteeringWheelAngle(steeringWheelAngle);
        odcore::data::Container container(vehicleControl);
        getConference().send(container);
    }

} // namespace SimulationGame
