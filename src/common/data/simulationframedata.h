#pragma once

#include <cstdint>
#include <string>

namespace Common {

    class FrameTime {
    public:
        FrameTime() = default;
        FrameTime(uint32_t frame);

    public:
        void setComputationTime(uint32_t computationTime);
        uint32_t getComputationTime() const;
        std::string toString() const;

    public:
        FrameTime& operator=(const FrameTime& other);

    private:
        uint32_t frame = 0;
        uint32_t compTime = 0;
    };

    class FrameMemory {
    public:
        FrameMemory() = default;
        FrameMemory(uint32_t frame);

    public:
        void setMemoryBeforeFrame(uint64_t memBeforeFrame);
        void setMemoryDuringFrame(uint64_t memDuringFrame);
        void setMemoryAfterFrame(uint64_t memAfterFrame);

        std::string toString() const;
        uint64_t sum() const;
        uint64_t average() const;
        uint64_t minimum() const;
        uint64_t maximum() const;

    public:
        FrameMemory& operator=(const FrameMemory& other);

    private:
        uint32_t frame = 0;
        uint64_t before = 0;
        uint64_t during = 0;
        uint64_t after = 0;

        const uint8_t parts = 3;
    };

    class FrameSteeringWheelAngle {
      public:
        FrameSteeringWheelAngle() = default;
        FrameSteeringWheelAngle(uint32_t frame, double angle);

    public:
        void setAngle(double value);
        double getAngle() const;
        std::string toString() const;

    private:
        uint32_t frame = 0;
        double angle = 0;
    };

} // namespace Common

