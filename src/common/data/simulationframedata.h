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
        void setMemoryBeforeFrame(uint32_t memBeforeFrame);
        void setMemoryDuringFrame(uint32_t memDuringFrame);
        void setMemoryAfterFrame(uint32_t memAfterFrame);

        std::string toString() const;
        uint32_t sum() const;
        uint32_t average() const;
        uint32_t minimum() const;
        uint32_t maximum() const;

    public:
        FrameMemory& operator=(const FrameMemory& other);

    private:
        uint32_t frame = 0;
        uint32_t before = 0;
        uint32_t during = 0;
        uint32_t after = 0;

        const uint8_t parts = 3;
    };

} // namespace Common

