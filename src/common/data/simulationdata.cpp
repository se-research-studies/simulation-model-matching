#include "simulationdata.h"

namespace Common {

    SimulationData::SimulationData(const std::string& simulationName, const std::string& recordingName)
        : simulationName(simulationName), recordingName(recordingName) {
    }

    std::string SimulationData::getSimulationName() const {
        return simulationName;
    }

    std::string SimulationData::getRecordingName() const {
        return recordingName;
    }

    uint32_t SimulationData::getFrames() const {
        return frames;
    }

    void SimulationData::setFrames(uint32_t value) {
        frames = value;
    }

    uint32_t SimulationData::getAverageComputationTime() const {
        return totalComputationTime / frames;
    }

    void SimulationData::addComputationTime(const FrameTime& value)
    {
        totalComputationTime += value.getComputationTime();
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

    uint32_t SimulationData::getLapTime() const {
        return lapTime;
    }

    void SimulationData::setLapTime(uint32_t value) {
        lapTime = value;
    }

    uint32_t SimulationData::getSteeringActions() const {
        return steeringActions;
    }

    void SimulationData::setSteeringActions(uint32_t value) {
        steeringActions = value;
    }

    void SimulationData::addSteeringAction() {
        ++steeringActions;
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

    uint32_t SimulationData::getAverageMemory() const {
        return totalMemory / (frames  * 3);
    }

    void SimulationData::addFrameMemory(const FrameMemory& value)
    {
        totalMemory += value.sum();
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
