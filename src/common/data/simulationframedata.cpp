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

    void FrameMemory::setMemoryBeforeFrame(size_t memBeforeFrame)
    {
        before = memBeforeFrame;
    }

    void FrameMemory::setMemoryDuringFrame(size_t memDuringFrame)
    {
        during = memDuringFrame;
    }

    void FrameMemory::setMemoryAfterFrame(size_t memAfterFrame)
    {
        after = memAfterFrame;
    }

    std::string FrameMemory::toString() const
    {
        return "{" + std::to_string(frame) + "," + std::to_string(before) + "," + std::to_string(during) + "," + std::to_string(after) + "}";
    }

    size_t FrameMemory::sum() const
    {
        return before + during + after;
    }

    size_t FrameMemory::average() const
    {
        return sum() / 3;
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
