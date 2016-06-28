#pragma once

#include <unordered_map>

#include <opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h>
#include <automotivedata/generated/automotive/VehicleControl.h>
#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/odcore/wrapper/SharedMemory.h>
#include <automotivedata/generated/cartesian/Point2.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/Common/makeunique.h>
#include <FeatureSimulation/Common/Data/featureset.h>
#include <FeatureSimulation/Common/Data/rectangle.h>
#include <FeatureSimulation/Common/Data/permutation.h>

#include <FeatureSimulation/SimulationGame/datagatherer.h>

namespace SimulationGame {

    class Settings;

    class AbstractParticipant : public odcore::base::module::TimeTriggeredConferenceClientModule
    {
    public:
        AbstractParticipant(int argc, char** argv, const std::string& name);
        virtual ~AbstractParticipant();

    public:
        template <typename SubClass>
        static std::unique_ptr<AbstractParticipant> createInstance(int argc, char** argv) {
            static_assert(std::is_base_of<AbstractParticipant, SubClass>(), "Only use createInstance with AbstractParticipant subclasses");
            return std::make_unique<SubClass>(argc, argv);
        }

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode runModule(const Settings& settings, Common::LocalFeatureSets&& localFeatureSets);
        void forceQuit();

        void setUp() override;
        void tearDown() override;
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() override;

    protected:
        virtual void processImage(const cv::Mat& image) = 0;
        void setControls(double speed, double steeringWheelAngle);

    private:
        bool continueBody();
        void processFrame(const odcore::data::image::SharedImage& sharedImage);
        cv::Mat prepareImage(const odcore::data::image::SharedImage& sharedImage, const std::shared_ptr<odcore::wrapper::SharedMemory>& sharedImageMemory);
        void gatherDataBeforeSimulation();
        void gatherDataBeforeFrame();
        void gatherDataDuringFrame(double speed, double steeringWheelAngle);
        void gatherDataAfterFrame();
        void gatherDataAfterSimulation();
        void addFeatures(cv::Mat& image);
        bool liesInRectangle(cartesian::Point2& point, const Common::Rectangle& rectangle) const;
        void addFeaturesFromFrame(cv::Mat& image, const Common::DirtyFrame& dirtyFrame) const;

    private:
        uint32_t frameLimit = 0;
        uint32_t currentFrame = 0;
        uint32_t currentFrameInSegment = 0;
        bool showGui;
        bool quitFlag = false;
        Common::LocalFeatureSets localFeatureSets;
        Common::Rectangle lastSegment;
        float featureScale = 0;
        int featureSize = 0;

        DataGatherer dataGatherer;
        automotive::VehicleControl vehicleControl;
    };

} // namespace SimulationGame

