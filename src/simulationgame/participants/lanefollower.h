#pragma once

#include <FeatureSimulation/SimulationGame/abstractparticipant.h>

namespace SimulationGame {

    class LaneFollower : public AbstractParticipant
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

