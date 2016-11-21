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

        std::string getCorrelationFile() const;
        void setCorrelationFile(const std::string& value);

        std::string getId() const;
        void setId(const std::string& value);

        std::string getPermutationIndex() const;
        void setPermutationIndex(const std::string& value);

        uint32_t getFrames() const;
        void setFrames(uint32_t value);

        uint32_t getAverageComputationTime() const;
        uint32_t getMinComputationTime() const;
        uint32_t getMaxComputationTime() const;
        void addComputationTime(const FrameTime& value);
        std::string computationTimesToString() const;
        uint64_t getTotalComputationTime() const;

        double getAverageLeftSteeringWheelAngle() const;
        double getAverageRightSteeringWheelAngle() const;
        double getMaxSteeringWheelAngle() const;
        uint32_t getLeftSteerings() const;
        uint32_t getRightSteerings() const;
        void addSteeringWheelAngle(const FrameSteeringWheelAngle& value);
        std::string steeringWheelAnglesToString() const;

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
        std::string correlationFile;
        std::string id;
        std::string permutationIndex;
        uint32_t frames = 0;
        uint32_t accelerations = 0;
        uint32_t decelerations = 0;        
        std::vector<FrameTime> computationTimes;
        std::vector<FrameMemory> memory;
        std::vector<FrameSteeringWheelAngle> steeringWheelAngles;
    };

} // namespace Common

