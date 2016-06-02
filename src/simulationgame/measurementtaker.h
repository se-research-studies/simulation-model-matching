#pragma once

#include <chrono>
#include <string>

#include <FeatureSimulation/Common/DataManagement/measurementsdao.h>

using namespace Common;

class MeasurementTaker {
public:
    MeasurementTaker(const std::string& simulationName, const std::string& recordingName);

public:
    void start();
    void startStep();
    void finishStep();
    void stop();
    void save();
    void addSteeringAction();

private:
    uint32_t passedMilliSecs(const std::chrono::steady_clock::time_point& since);

private:
    Measurements measurements;

    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point stepStartTime;

private:
    MeasurementsDAO dao;
};
