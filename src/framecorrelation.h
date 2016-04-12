#pragma once

#include <cstdint>

#include <NoiseSimulation/Savable>
#include <NoiseSimulation/Sequence>

namespace NoiseSimulation {

    class FrameCorrelation : public Savable
    {
    public:
        FrameCorrelation();
        virtual ~FrameCorrelation();

    public:
        std::map<std::string, std::string> toMap() const override;

    private:
        uint32_t id;
        Sequence videoSequence;
        Sequence simulationSequence;
    };

} // namespace NoiseSimulation

