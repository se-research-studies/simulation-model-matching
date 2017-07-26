#pragma once

#include <FeatureSimulation/SimulationGame/abstractautopilot.h>

namespace SimulationGame {

    class LaneFollower : public AbstractAutopilot
    {
    public:
        LaneFollower(int argc, char** argv);
        virtual ~LaneFollower();

    private:
        void processImage(const cv::Mat& image) override;

    private:
        odcore::data::TimeStamp m_previousTime;
        double m_eSum;
        double m_eOld;
    };

} // namespace SimulationGame

