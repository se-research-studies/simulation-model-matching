#include "simulationdata.h"

namespace Common {

    SimulationData::SimulationData() {
    }

    std::string SimulationData::getSimulationName() const {
        return simulationName;
    }

    void SimulationData::setSimulationName(const std::string& value)
    {
        simulationName = value;
    }

    std::string SimulationData::getCorrelationFile() const {
        return correlationFile;
    }

    void SimulationData::setCorrelationFile(const std::string& value)
    {
        correlationFile = value;
    }

    uint32_t SimulationData::getFrames() const {
        return frames;
    }

    void SimulationData::setFrames(uint32_t value) {
        frames = value;
    }

    uint32_t SimulationData::getAverageComputationTime() const {
        uint32_t totalComputationTime = 0;
        for (const FrameTime& frameTime : computationTimes) {
            totalComputationTime += frameTime.getComputationTime();
        }
        uint32_t result = totalComputationTime / frames;
        return result;
    }

    uint32_t SimulationData::getMinComputationTime() const
    {
        uint32_t minComputationTime = 0;
        if (computationTimes.size() > 0) {
            minComputationTime = computationTimes.at(0).getComputationTime();
        }
        for (const FrameTime& frameTime : computationTimes) {
            minComputationTime = std::min(minComputationTime, frameTime.getComputationTime());
        }
        return minComputationTime;
    }

    uint32_t SimulationData::getMaxComputationTime() const
    {
        uint32_t maxComputationTime = 0;
        for (const FrameTime& frameTime : computationTimes) {
            maxComputationTime = std::max(maxComputationTime, frameTime.getComputationTime());
        }
        return maxComputationTime;
    }

    void SimulationData::addComputationTime(const FrameTime& value)
    {
        computationTimes.push_back(value);
    }

    std::string SimulationData::computationTimesToString() const
    {
        std::string result = "{";
        for (const FrameTime& time : computationTimes) {
            result += time.toString() + ",";
        }
        result.pop_back();
        result += "}";
        return result;
    }

    uint64_t SimulationData::getLapTime() const {
        uint32_t result = 0;
        for (const FrameTime& frameTime : computationTimes) {
            result += frameTime.getComputationTime();
        }
        return result;
    }

    uint32_t SimulationData::getLeftSteerings() const
    {
        return leftSteerings;
    }

    void SimulationData::setLeftSteerings(uint32_t value)
    {
        leftSteerings = value;
    }

    void SimulationData::addLeftSteering()
    {
        ++leftSteerings;
    }

    uint32_t SimulationData::getRightSteerings() const
    {
        return rightSteerings;
    }

    void SimulationData::setRightSteerings(uint32_t value)
    {
        rightSteerings = value;
    }

    void SimulationData::addRightSteering()
    {
        ++rightSteerings;
    }

    uint32_t SimulationData::getAccelerations() const
    {
        return accelerations;
    }

    void SimulationData::setAccelerations(uint32_t value)
    {
        accelerations = value;
    }

    void SimulationData::addAcceleration()
    {
        ++accelerations;
    }

    uint32_t SimulationData::getDecelerations() const
    {
        return decelerations;
    }

    void SimulationData::setDecelerations(uint32_t value)
    {
        decelerations = value;
    }

    void SimulationData::addDeceleration()
    {
        ++decelerations;
    }

    uint64_t SimulationData::getAverageMemory() const {
        uint64_t totalAverageMemory = 0;
        for (const FrameMemory& frameMemory : memory) {
            totalAverageMemory += frameMemory.average();
        }
        uint64_t result = totalAverageMemory / frames;
        return result;
    }

    uint64_t SimulationData::getMinMemory() const
    {
        uint64_t minMemory = 0;
        if (memory.size() > 0) {
            minMemory = memory.at(0).minimum();
        }
        for (const FrameMemory& frameMemory : memory) {
            minMemory = std::min(minMemory, frameMemory.minimum());
        }
        return minMemory;
    }

    uint64_t SimulationData::getMaxMemory() const
    {
        uint64_t maxMemory = 0;
        for (const FrameMemory& frameMemory : memory) {
            maxMemory = std::max(maxMemory, frameMemory.maximum());
        }
        return maxMemory;
    }

    void SimulationData::addFrameMemory(const FrameMemory& value)
    {
        memory.push_back(value);
    }

    std::string SimulationData::memoryToString() const
    {
        std::string result = "{";
        for (const FrameMemory& frameMemory : memory) {
            result += frameMemory.toString() + ",";
        }
        result.pop_back();
        result += "}";
        return result;
    }
    
} // namespace Common
