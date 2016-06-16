#include "datagatherer.h"

#include <FeatureSimulation/Common/Data/measurements.h>

namespace SimulationGame {

    DataGatherer::DataGatherer(const std::string& simulationName, const std::string& recordingName)
        : measurements(simulationName, recordingName) {
    }

    void DataGatherer::start() {
        dao.ensureTable();
        startTime = std::chrono::steady_clock::now();
    }

    void DataGatherer::startStep() {
        stepStartTime = std::chrono::steady_clock::now();
        measurements.addFrame();
    }

    void DataGatherer::finishStep() {
        //measurements.addToComputationTime(passedMilliSecs(stepStartTime));
    }

    void DataGatherer::stop() {
        measurements.setLapTime(passedMilliSecs(startTime));
    }

    void DataGatherer::save() {
        dao.save(measurements);
    }

    void DataGatherer::addSteeringAction() {
        measurements.addSteeringAction();
    }

    uint32_t DataGatherer::passedMilliSecs(const std::chrono::_V2::steady_clock::time_point& since) {
        const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - since).count();
    }

    void DataGatherer::addAcceleration()
    {
        //measurements
    }

    void DataGatherer::addDeceleration()
    {

    }

}
