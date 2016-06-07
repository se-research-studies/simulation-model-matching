#pragma once

#include <chrono>
#include <string>

#include "measurementsdao.h"
#include "measurements.h"

class MeasurementTaker {
public:
    MeasurementTaker(const std::string& simulationName, const std::string& recordingName);

public:
    // Called once at the beginning of the body. Creates the table and caches the start time (used for lap time)
    void start();

    // Called for each frame before processImage() is called.
    void startStep();

    // Calles for each frame after processImage(). Adds the time processImage took to the computationTime.
    void finishStep();

    // Called once at the end of the body. Sets the lap time
    void stop();

    // Called once at the end of the body. Saves the measurements
    void save();

    // Called each a change in steering angle is detected
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
