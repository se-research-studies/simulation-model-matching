#pragma once

#include <chrono>
#include <string>

#include <FeatureSimulation/Common/Data/simulationdata.h>
#include <FeatureSimulation/Common/Data/simulationframedata.h>
#include <FeatureSimulation/Common/DataManagement/simulationdatadao.h>

namespace SimulationGame {

    class DataGatherer {
    public:
        DataGatherer(const std::string& simulationName, const std::string& recordingName);

    public:
        void start();
        void startFrame();
        void midFrame(double speed, double steeringWheelAngle);
        void finishFrame();
        void stop();
        void save();

    private:
        uint32_t passedMilliSecs(const std::chrono::steady_clock::time_point& since);
        uint32_t passedMicroSecs(const std::chrono::steady_clock::time_point& since);
        size_t getCurrentMemoryUsage();

    private:
        Common::SimulationData data;

        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point frameStartTime;
        Common::FrameMemory frameMemory;
        Common::FrameTime frameTime;
        uint32_t frames = 0;

        double lastSteeringWheelAngle = 0;
        double lastSpeed = 0;

    private:
        Common::SimulationDataDAO dao;
    };

}
