#include "measurements.h"

namespace Common {

    Measurements::FrameMemory::FrameMemory(uint32_t frame, uint32_t before, uint32_t during, uint32_t after)
        : frame(frame), before(before), during(during), after(after)
    {
    }

    std::string Measurements::FrameMemory::toString() const
    {
        return "{" + std::to_string(frame) + "," + std::to_string(before) + "," + std::to_string(during) + "," + std::to_string(after) + "}";
    }

    uint32_t Measurements::FrameMemory::sum() const
    {
        return before + during + after;
    }

    uint32_t Measurements::FrameMemory::average() const
    {
        return sum() / 3;
    }


    Measurements::FrameTime::FrameTime(uint32_t frame, uint32_t computationTime)
        : frame(frame), computationTime(computationTime)
    {
    }

    std::string Measurements::FrameTime::toString() const
    {
        return "{" + std::to_string(frame) + "," + std::to_string(computationTime) + "}";
    }


    Measurements::Measurements(const std::string& simulationName, const std::string& recordingName)
        : simulationName(simulationName), recordingName(recordingName) {
    }

    std::string Measurements::getSimulationName() const {
        return simulationName;
    }

    std::string Measurements::getRecordingName() const {
        return recordingName;
    }

    uint32_t Measurements::getFrames() const {
        return frames;
    }

    void Measurements::setFrames(uint32_t value) {
        frames = value;
    }

    void Measurements::addFrame() {
        ++frames;
    }

    uint32_t Measurements::getAverageComputationTime() const {
        return totalComputationTime / frames;
    }

    void Measurements::addComputationTime(Measurements::FrameTime&& value)
    {
        totalComputationTime += value.computationTime;
        computationTimes.push_back(std::move(value));
    }

    std::string Measurements::computationTimesToString() const
    {
        std::string result = "{";
        for (const FrameTime& time : computationTimes) {
            result += time.toString() + ",";
        }
        result.pop_back();
        result += "}";
        return result;
    }

    uint32_t Measurements::getLapTime() const {
        return lapTime;
    }

    void Measurements::setLapTime(uint32_t value) {
        lapTime = value;
    }

    uint32_t Measurements::getSteeringActions() const {
        return steeringActions;
    }

    void Measurements::setSteeringActions(uint32_t value) {
        steeringActions = value;
    }

    void Measurements::addSteeringAction() {
        ++steeringActions;
    }

    uint32_t Measurements::getAccelerations() const
    {
        return accelerations;
    }

    void Measurements::setAccelerations(uint32_t value)
    {
        accelerations = value;
    }

    void Measurements::addAcceleration()
    {
        ++accelerations;
    }

    uint32_t Measurements::getDecelerations() const
    {
        return decelerations;
    }

    void Measurements::setDecelerations(uint32_t value)
    {
        decelerations = value;
    }

    void Measurements::addDeceleration()
    {
        ++decelerations;
    }

    uint32_t Measurements::getAverageMemory() const {
        return totalMemory / frames;
    }

    void Measurements::addFrameMemory(Measurements::FrameMemory&& value)
    {
        totalMemory += value.sum();
        memory.push_back(std::move(value));
    }

    std::string Measurements::memoryToString() const
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
