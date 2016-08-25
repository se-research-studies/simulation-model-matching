#include "datagatherer.h"

#include <unistd.h>
#include <sys/resource.h>

#include <FeatureSimulation/Common/utils.h>

namespace SimulationGame {

    DataGatherer::DataGatherer()
        : frameMemory(0) {
    }

    void DataGatherer::setSimulationName(const std::string& value)
    {
        data.setSimulationName(value);
    }

    void DataGatherer::setCorrelationFile(const std::string& value)
    {
        data.setCorrelationFile(value);
    }

    void DataGatherer::setId(const std::string& value)
    {
        data.setId(value);
    }

    void DataGatherer::setPermutationIndex(const std::string& value)
    {
        data.setPermutationIndex(value);
    }

    void DataGatherer::start() {
        dao.ensureTable();
        frames = 0;
    }

    void DataGatherer::startFrame() {
        ++frames;
        frameMemory = Common::FrameMemory(frames);
        frameTime = Common::FrameTime(frames);
        frameMemory.setMemoryBeforeFrame(getCurrentMemoryUsageInKb());
        frameStartTime = std::chrono::steady_clock::now();
    }

    void DataGatherer::midFrame(double speed, double steeringWheelAngle)
    {
        // To not add the time this takes to the frame time the start time is stored and at the and the frameStartTime adapted
        std::chrono::steady_clock::time_point midFrameStart = std::chrono::steady_clock::now();
        frameMemory.setMemoryDuringFrame(getCurrentMemoryUsageInKb());
        data.addSteeringWheelAngle(Common::FrameSteeringWheelAngle(frames, steeringWheelAngle));
        lastSteeringWheelAngle = steeringWheelAngle;
        compareSpeed(speed);
        frameStartTime += (std::chrono::steady_clock::now() - midFrameStart);
    }

    void DataGatherer::compareSpeed(double speed)
    {
        int speedComparison = Common::Utils::compare(speed, lastSpeed);
        if (speedComparison == 1) {
            data.addAcceleration();
        } else if (speedComparison == -1) {
            data.addDeceleration();
        }
        lastSpeed = speed;
    }

    void DataGatherer::finishFrame() {
        frameTime.setComputationTime(passedMicroSecs(frameStartTime));
        frameMemory.setMemoryAfterFrame(getCurrentMemoryUsageInKb());
        data.addComputationTime(frameTime);
        data.addFrameMemory(frameMemory);
    }

    void DataGatherer::stop() {
        data.setFrames(frames);
    }

    void DataGatherer::save() {
        dao.save(data);
    }

    uint32_t DataGatherer::passedMicroSecs(const std::chrono::_V2::steady_clock::time_point& since)
    {
        const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        return Common::Utils::to<uint32_t>(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - since).count());
    }

    uint64_t DataGatherer::getCurrentMemoryUsageInKb()
    {
        FILE* fp = fopen( "/proc/self/statm", "r" );
        if (fp == nullptr) {
            return 0;
        }
        uint64_t rss = 0;
        if (fscanf(fp, "%*s%ld", &rss) != 1) {
            fclose(fp);
            return 0;
        }
        fclose(fp);
        uint64_t bytes = rss * Common::Utils::to<uint64_t>(sysconf(_SC_PAGESIZE));
        return bytes / 1024;
    }

}
