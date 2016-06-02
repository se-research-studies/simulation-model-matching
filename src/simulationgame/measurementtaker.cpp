#include "measurementtaker.h"

#include <FeatureSimulation/Common/Data/measurements.h>

using namespace Common;

MeasurementTaker::MeasurementTaker(const std::string& simulationName, const std::string& recordingName)
    : measurements(simulationName, recordingName) {
}

void MeasurementTaker::start() {
    dao.ensureTable();
    startTime = std::chrono::steady_clock::now();
}

void MeasurementTaker::startStep() {
    stepStartTime = std::chrono::steady_clock::now();
    measurements.addStep();
}

void MeasurementTaker::finishStep() {
    measurements.addToComputationTime(passedMilliSecs(stepStartTime));
}

void MeasurementTaker::stop() {
    measurements.setLapTime(passedMilliSecs(startTime));
}

void MeasurementTaker::save() {
    dao.save(measurements);
}

void MeasurementTaker::addSteeringAction() {
    measurements.addSteeringAction();
}

uint32_t MeasurementTaker::passedMilliSecs(const std::chrono::_V2::steady_clock::time_point& since) {
    const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - since).count();
}
