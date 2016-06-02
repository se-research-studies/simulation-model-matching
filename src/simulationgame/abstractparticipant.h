#pragma once

#include <opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace SimulationGame {

    class AbstractParticipant : public odcore::base::module::TimeTriggeredConferenceClientModule
    {
    public:
        AbstractParticipant(int argc, char** argv, const std::string& name);
        virtual ~AbstractParticipant();

    public:
        template <typename SubClass> static AbstractParticipant&& createInstance(int argc, char** argv) {
            return SubClass(argc, argv);
        }

        void setUp() override;
        void tearDown() override;
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() override;

    protected:
        virtual void processImage(const cv::Mat& image) = 0;

    private:
        bool readSharedImage(odcore::data::Container& container);

    private:
        bool guiEnabled;

//        automotive::VehicleControl m_vehicleControl;
    };

} // namespace SimulationGame

