#pragma once

#include <chrono>
#include <string>

#include <FeatureSimulation/Common/DataManagement/measurementsdao.h>

namespace SimulationGame {

    class DataGatherer {
    public:
        DataGatherer(const std::string& simulationName, const std::string& recordingName);

    public:
        void start();
        void startStep();
        void finishStep();
        void stop();
        void save();
        void addSteeringAction();
        void addAcceleration();
        void addDeceleration();

    private:
        uint32_t passedMilliSecs(const std::chrono::steady_clock::time_point& since);

    private:
        Common::Measurements measurements;

        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point stepStartTime;

    private:
        Common::MeasurementsDAO dao;
    };

}
