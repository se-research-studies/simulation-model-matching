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

        // Members from LaneFollower.h:
//        bool m_hasAttachedToSharedImageMemory;
//        std::shared_ptr<odcore::wrapper::SharedMemory> m_sharedImageMemory;
//        IplImage *m_image;
//        bool m_debug;
//        CvFont m_font;

//        odcore::data::TimeStamp m_previousTime;
//        double m_eSum;
//        double m_eOld;

//        automotive::VehicleControl m_vehicleControl;
    };

} // namespace SimulationGame

