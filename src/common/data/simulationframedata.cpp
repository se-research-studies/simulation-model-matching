#include "simulationframedata.h"

namespace Common {

    FrameTime::FrameTime(uint32_t frame)
        : frame(frame)
    {
    }

    void FrameTime::setComputationTime(uint32_t computationTime)
    {
        compTime = computationTime;
    }

    uint32_t FrameTime::getComputationTime() const
    {
        return compTime;
    }

    std::string FrameTime::toString() const
    {
        return "{" + std::to_string(frame) + "," + std::to_string(compTime) + "}";
    }

    FrameTime& FrameTime::operator=(const FrameTime& other)
    {
        frame = other.frame;
        compTime = other.compTime;
        return *this;
    }




    FrameMemory::FrameMemory(uint32_t frame)
        : frame(frame)
    {
    }

    void FrameMemory::setMemoryBeforeFrame(uint32_t memBeforeFrame)
    {
        before = memBeforeFrame;
    }

    void FrameMemory::setMemoryDuringFrame(uint32_t memDuringFrame)
    {
        during = memDuringFrame;
    }

    void FrameMemory::setMemoryAfterFrame(uint32_t memAfterFrame)
    {
        after = memAfterFrame;
    }

    std::string FrameMemory::toString() const
    {
        return "{" + std::to_string(frame) + "," + std::to_string(before) + "," + std::to_string(during) + "," + std::to_string(after) + "}";
    }

    uint32_t FrameMemory::sum() const
    {
        return before + during + after;
    }

    uint32_t FrameMemory::average() const
    {
        return sum() / parts;
    }

    uint32_t FrameMemory::minimum() const
    {
        uint32_t min = before;
        min = std::min(min, during);
        min = std::min(min, after);
        return min;
    }

    uint32_t FrameMemory::maximum() const
    {
        uint32_t max = before;
        max = std::max(max, during);
        max = std::max(max, after);
        return max;
    }

    FrameMemory& FrameMemory::operator=(const FrameMemory& other)
    {
        frame = other.frame;
        before = other.before;
        during = other.during;
        after = other.after;
        return *this;
    }

} // namespace Common
