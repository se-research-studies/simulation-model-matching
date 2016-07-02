#include "simulationdata.h"

#include <math.h>

#include <FeatureSimulation/Common/utils.h>

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

    std::string SimulationData::getPermutationIndex() const
    {
        return permutationIndex;
    }

    void SimulationData::setPermutationIndex(const std::string& value)
    {
        permutationIndex = value;
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

    uint64_t SimulationData::getTotalComputationTime() const {
        uint64_t result = 0;
        for (const FrameTime& frameTime : computationTimes) {
            result += frameTime.getComputationTime();
        }
        return result;
    }

    double SimulationData::getAverageLeftSteeringWheelAngle() const
    {
        double angleSum = 0;
        uint32_t count = 0;
        for (const FrameSteeringWheelAngle& angle : steeringWheelAngles) {
            if (Common::Utils::compare(angle.getAngle(), 0.0) == -1) {
                angleSum += fabs(angle.getAngle());
                ++count;
            }
        }
        double result = angleSum / count;
        return result;
    }

    double SimulationData::getAverageRightSteeringWheelAngle() const
    {
        double angleSum = 0;
        uint32_t count = 0;
        for (const FrameSteeringWheelAngle& angle : steeringWheelAngles) {
            if (Common::Utils::compare(angle.getAngle(), 0.0) == 1) {
                angleSum += angle.getAngle();
                ++count;
            }
        }
        double result = angleSum / count;
        return result;
    }

    double SimulationData::getMaxSteeringWheelAngle() const
    {
        double result = 0;
        for (const FrameSteeringWheelAngle& angle : steeringWheelAngles) {
            if (fabs(result) < fabs(angle.getAngle())) {
                result = angle.getAngle();
            }
        }
        return result;
    }

    uint32_t SimulationData::getLeftSteerings() const
    {
        uint32_t result = 0;
        for (const FrameSteeringWheelAngle& angle : steeringWheelAngles) {
            if (Common::Utils::compare(angle.getAngle(), 0.0) == -1) {
                ++result;
            }
        }
        return result;
    }

    uint32_t SimulationData::getRightSteerings() const
    {
        uint32_t result = 0;
        for (const FrameSteeringWheelAngle& angle : steeringWheelAngles) {
            if (Common::Utils::compare(angle.getAngle(), 0.0) == 1) {
                ++result;
            }
        }
        return result;
    }

    void SimulationData::addSteeringWheelAngle(const FrameSteeringWheelAngle& value)
    {
        steeringWheelAngles.push_back(value);
    }

    std::string SimulationData::steeringWheelAnglesToString() const
    {
        std::string result = "{";
        for (const FrameSteeringWheelAngle& angle : steeringWheelAngles) {
            result += angle.toString() + ",";
        }
        result.pop_back();
        result += "}";
        return result;
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
