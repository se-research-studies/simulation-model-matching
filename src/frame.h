#pragma once

#include <cstdint>

namespace NoiseSimulation {

    class Recording;

    class Frame
    {
    public:
        Frame(Recording* recording, uint32_t index);
        virtual ~Frame();

    public:
        const Recording* getRecording() const;
        uint32_t getIndex() const;

    private:
        const Recording* recording;
        const uint32_t index;
    };

} // namespace NoiseSimulation

