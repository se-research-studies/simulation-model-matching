#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <FeatureSimulation/Common/Data/simulationframedata.h>

namespace Common {

    class SimulationData {
    public:
        SimulationData(const std::string& simulationName, const std::string& recordingName);

    public:        
        std::string getSimulationName() const;

        std::string getRecordingName() const;

        uint32_t getFrames() const;
        void setFrames(uint32_t value);

        uint32_t getAverageComputationTime() const;
        void addComputationTime(const FrameTime& value);
        std::string computationTimesToString() const;

        uint32_t getLapTime() const;
        void setLapTime(uint32_t value);

        uint32_t getSteeringActions() const;
        void setSteeringActions(uint32_t value);
        void addSteeringAction();

        uint32_t getAccelerations() const;
        void setAccelerations(uint32_t value);
        void addAcceleration();

        uint32_t getDecelerations() const;
        void setDecelerations(uint32_t value);
        void addDeceleration();

        uint32_t getAverageMemory() const;
        void addFrameMemory(const FrameMemory& value);
        std::string memoryToString() const;

    private:
        const std::string simulationName;
        const std::string recordingName;

        uint32_t frames = 0;

        uint32_t totalComputationTime = 0;
        std::vector<FrameTime> computationTimes;

        uint32_t lapTime = 0;

        uint32_t steeringActions = 0;
        uint32_t accelerations = 0;
        uint32_t decelerations = 0;

        uint32_t totalMemory = 0;
        std::vector<FrameMemory> memory;
    };

} // namespace Common

