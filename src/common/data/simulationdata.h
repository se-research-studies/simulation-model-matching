#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <FeatureSimulation/Common/Data/simulationframedata.h>

namespace Common {

    class SimulationData {
    public:
        SimulationData();

    public:        
        std::string getSimulationName() const;
        void setSimulationName(const std::string& value);

        std::string getRecordingName() const;
        void setRecordingName(const std::string& value);

        uint32_t getFrames() const;
        void setFrames(uint32_t value);

        uint32_t getAverageComputationTime() const;
        uint32_t getMinComputationTime() const;
        uint32_t getMaxComputationTime() const;
        void addComputationTime(const FrameTime& value);
        std::string computationTimesToString() const;

        uint64_t getLapTime() const;
        void setLapTime(uint64_t value);

        uint32_t getLeftSteerings() const;
        void setLeftSteerings(uint32_t value);
        void addLeftSteering();

        uint32_t getRightSteerings() const;
        void setRightSteerings(uint32_t value);
        void addRightSteering();

        uint32_t getAccelerations() const;
        void setAccelerations(uint32_t value);
        void addAcceleration();

        uint32_t getDecelerations() const;
        void setDecelerations(uint32_t value);
        void addDeceleration();

        uint64_t getAverageMemory() const;
        uint64_t getMinMemory() const;
        uint64_t getMaxMemory() const;
        void addFrameMemory(const FrameMemory& value);
        std::string memoryToString() const;        

    private:
        std::string simulationName;
        std::string recordingName;
        uint32_t frames = 0;
        uint64_t lapTime = 0;
        uint32_t leftSteerings = 0;
        uint32_t rightSteerings = 0;
        uint32_t accelerations = 0;
        uint32_t decelerations = 0;        
        std::vector<FrameTime> computationTimes;
        std::vector<FrameMemory> memory;
    };

} // namespace Common

