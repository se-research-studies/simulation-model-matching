#pragma once

#include <opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h>
#include <automotivedata/generated/automotive/VehicleControl.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/Common/makeunique.h>
#include <FeatureSimulation/Common/DataManagement/featuresetdao.h>

namespace SimulationGame {

    class AbstractParticipant : public odcore::base::module::TimeTriggeredConferenceClientModule
    {
    public:
        AbstractParticipant(int argc, char** argv, const std::string& name);
        virtual ~AbstractParticipant();

    public:
        template <typename SubClass> static std::unique_ptr<AbstractParticipant> createInstance(int argc, char** argv) {
            return std::make_unique<SubClass>(argc, argv);
        }

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode runModule(uint32_t frameLimit, const std::string& featureSource);

        void setUp() override;
        void tearDown() override;
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() override;

    protected:
        virtual void processImage(const cv::Mat& image) = 0;
        void setControls(double speed, double steeringWheelAngle);

    private:
        void addFeatures(cv::Mat& image, uint32_t frame) const;

    private:
        uint32_t frameLimit = 0;
        Common::FeatureSetDAO featureSetDao;
        std::unique_ptr<Common::FeatureSet> featureSet;
        automotive::VehicleControl vehicleControl;
    };

} // namespace SimulationGame

