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
        void setMemoryBeforeFrame(size_t memBeforeFrame);
        void setMemoryDuringFrame(size_t memDuringFrame);
        void setMemoryAfterFrame(size_t memAfterFrame);

        std::string toString() const;
        size_t sum() const;
        size_t average() const;

    public:
        FrameMemory& operator=(const FrameMemory& other);

    private:
        uint32_t frame = 0;
        size_t before = 0;
        size_t during = 0;
        size_t after = 0;
    };

} // namespace Common

