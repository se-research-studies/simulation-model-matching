#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Common {

    class Measurements {
    public:
        Measurements(const std::string& simulationName, const std::string& recordingName);

    public:
        struct FrameTime {
            FrameTime() = default;
            FrameTime(FrameTime&& other) = default;
            FrameTime(const FrameTime& other) = delete;
            FrameTime(uint32_t frame, uint32_t computationTime);

            uint32_t frame = 0;
            uint32_t computationTime = 0;

            std::string toString() const;
        };

        struct FrameMemory {
            FrameMemory() = default;
            FrameMemory(FrameMemory&& other) = default;
            FrameMemory(const FrameMemory& other) = delete;
            FrameMemory(uint32_t frame, uint32_t before, uint32_t during, uint32_t after);

            uint32_t frame = 0;
            uint32_t before = 0;
            uint32_t during = 0;
            uint32_t after = 0;

            std::string toString() const;
            uint32_t sum() const;
            uint32_t average() const;
        };

    public:        
        std::string getSimulationName() const;

        std::string getRecordingName() const;

        uint32_t getFrames() const;
        void setFrames(uint32_t value);
        void addFrame();

        uint32_t getAverageComputationTime() const;
        void addComputationTime(FrameTime&& value);
        std::string computationTimesToString() const;

        uint32_t getLapTime() const;
        void setLapTime(uint32_t value);

        uint32_t getSteeringActions() const;
        void setSteeringActions(uint32_t value);
        void addSteeringAction();

        uint32_t getAccelerations() const;
        void setAccelerations(uint32_t value);
        void addAcceleration();

        uint32_t getDecelerations() const;
        void setDecelerations(uint32_t value);
        void addDeceleration();

        uint32_t getAverageMemory() const;
        void addFrameMemory(FrameMemory&& value);
        std::string memoryToString() const;

    private:
        const std::string simulationName;
        const std::string recordingName;

        uint32_t frames = 0;

        uint32_t totalComputationTime = 0;
        std::vector<FrameTime> computationTimes;

        uint32_t lapTime = 0;

        uint32_t steeringActions = 0;
        uint32_t accelerations = 0;
        uint32_t decelerations = 0;

        uint32_t totalMemory = 0;
        std::vector<FrameMemory> memory;
    };

} // namespace Common

