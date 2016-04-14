#include "frame.h"

namespace NoiseSimulation {

    Frame::Frame(Recording* recording, uint32_t index)
        : recording(recording), index(index)
    {
    }

    Frame::~Frame()
    {
    }

    const Recording* Frame::getRecording() const
    {
        return recording;
    }

    uint32_t Frame::getIndex() const
    {
        return index;
    }

} // namespace NoiseSimulation
