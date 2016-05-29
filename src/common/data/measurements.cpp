#include "measurements.h"

namespace Common {

    Measurements::Measurements(const std::string& simulationName, const std::string& recordingName)
        : simulationName(simulationName), recordingName(recordingName) {
    }

    std::string Measurements::getSimulationName() const {
        return simulationName;
    }

    std::string Measurements::getRecordingName() const {
        return recordingName;
    }

    uint32_t Measurements::getSteps() const {
        return steps;
    }

    void Measurements::setSteps(uint32_t value) {
        steps = value;
    }

    void Measurements::addStep() {
        ++steps;
    }

    uint32_t Measurements::getComputationTime() const {
        return computationTime;
    }

    void Measurements::setComputationTime(uint32_t value) {
        computationTime = value;
    }

    void Measurements::addToComputationTime(uint32_t value) {
        computationTime += value;
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

    uint32_t Measurements::getMemory() const {
        return memory;
    }

    void Measurements::setMemory(uint32_t value) {
        memory = value;
    }

} // namespace Common
