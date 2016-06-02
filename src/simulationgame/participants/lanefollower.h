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
    };

} // namespace SimulationGame

