#include "datagatherer.h"

#include <unistd.h>
#include <sys/resource.h>

namespace SimulationGame {

    DataGatherer::DataGatherer(const std::string& simulationName, const std::string& recordingName)
        : data(simulationName, recordingName), frameMemory(0) {
    }

    void DataGatherer::start() {
        dao.ensureTable();
        frames = 0;
        startTime = std::chrono::steady_clock::now();
    }

    void DataGatherer::startFrame() {
        ++frames;
        frameMemory = Common::FrameMemory(frames);
        frameTime = Common::FrameTime(frames);
        frameMemory.setMemoryBeforeFrame(getCurrentMemoryUsage());
        frameStartTime = std::chrono::steady_clock::now();
    }

    void DataGatherer::midFrame(double speed, double steeringWheelAngle)
    {
        std::chrono::steady_clock::time_point midFrameStart = std::chrono::steady_clock::now();
        frameMemory.setMemoryDuringFrame(getCurrentMemoryUsage());
        if (steeringWheelAngle != lastSteeringWheelAngle) {
            data.addSteeringAction();
        }
        if (speed > lastSpeed) {
            data.addAcceleration();
        } else if (speed < lastSpeed) {
            data.addDeceleration();
        }
        lastSteeringWheelAngle = steeringWheelAngle;
        lastSpeed = speed;
        frameStartTime += (std::chrono::steady_clock::now() - midFrameStart);
    }

    void DataGatherer::finishFrame() {
        frameTime.setComputationTime(passedMicroSecs(frameStartTime));
        frameMemory.setMemoryAfterFrame(getCurrentMemoryUsage());
        data.addComputationTime(frameTime);
        data.addFrameMemory(frameMemory);
    }

    void DataGatherer::stop() {
        data.setLapTime(passedMilliSecs(startTime));
        data.setFrames(frames);
    }

    void DataGatherer::save() {
        dao.save(data);
    }

    uint32_t DataGatherer::passedMilliSecs(const std::chrono::_V2::steady_clock::time_point& since) {
        const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - since).count();
    }

    uint32_t DataGatherer::passedMicroSecs(const std::chrono::_V2::steady_clock::time_point& since)
    {
        const std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(currentTime - since).count();
    }

    size_t DataGatherer::getCurrentMemoryUsage()
    {
        size_t rss = 0L;
        FILE* fp = fopen( "/proc/self/statm", "r" );
        if (fp == nullptr) {
            return 0;
        }
        if (fscanf(fp, "%*s%ld", &rss) != 1) {
            fclose(fp);
            return 0;
        }
        fclose(fp);
        return rss * sysconf(_SC_PAGESIZE);
    }

}
