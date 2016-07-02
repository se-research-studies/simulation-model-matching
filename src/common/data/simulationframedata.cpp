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

    void FrameMemory::setMemoryBeforeFrame(uint64_t memBeforeFrame)
    {
        before = memBeforeFrame;
    }

    void FrameMemory::setMemoryDuringFrame(uint64_t memDuringFrame)
    {
        during = memDuringFrame;
    }

    void FrameMemory::setMemoryAfterFrame(uint64_t memAfterFrame)
    {
        after = memAfterFrame;
    }

    std::string FrameMemory::toString() const
    {
        return "{" + std::to_string(frame) + "," + std::to_string(before) + "," + std::to_string(during) + "," + std::to_string(after) + "}";
    }

    uint64_t FrameMemory::sum() const
    {
        return before + during + after;
    }

    uint64_t FrameMemory::average() const
    {
        return sum() / parts;
    }

    uint64_t FrameMemory::minimum() const
    {
        uint64_t min = before;
        min = std::min(min, during);
        min = std::min(min, after);
        return min;
    }

    uint64_t FrameMemory::maximum() const
    {
        uint64_t max = before;
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




    FrameSteeringWheelAngle::FrameSteeringWheelAngle(uint32_t frame, double angle)
        : frame(frame), angle(angle)
    {
    }

    void FrameSteeringWheelAngle::setAngle(double value)
    {
        angle = value;
    }

    double FrameSteeringWheelAngle::getAngle() const
    {
        return angle;
    }

    std::string FrameSteeringWheelAngle::toString() const
    {
        return "{" + std::to_string(frame) + "," + std::to_string(angle) + "}";
    }

} // namespace Common
