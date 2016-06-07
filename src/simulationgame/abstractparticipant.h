#pragma once

#include <opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h>
#include <automotivedata/generated/automotive/VehicleControl.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/Common/makeunique.h>

namespace SimulationGame {

    class AbstractParticipant : public odcore::base::module::TimeTriggeredConferenceClientModule
    {
    public:
        AbstractParticipant(int argc, char** argv, const std::string& name, uint32_t frameLimit);
        virtual ~AbstractParticipant();

    public:
        template <typename SubClass> static std::unique_ptr<AbstractParticipant> createInstance(int argc, char** argv, uint32_t frameLimit) {
            return std::make_unique<SubClass>(argc, argv, frameLimit);
        }

        void setUp() override;
        void tearDown() override;
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() override;

    protected:
        virtual void processImage(const cv::Mat& image) = 0;
        void setControls(double speed, double steeringWheelAngle);

    private:
        bool readSharedImage(odcore::data::Container& container);

    private:
        uint32_t frameLimit = 0;

        automotive::VehicleControl vehicleControl;
    };

} // namespace SimulationGame

