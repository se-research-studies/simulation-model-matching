#pragma once

#include <cstdint>

#include <NoiseSimulation/Loadable>
#include <NoiseSimulation/Savable>
#include <NoiseSimulation/Sequence>

namespace NoiseSimulation {

    class Recording;

    class FrameCorrelation : public Savable, public Loadable
    {
    public:
        FrameCorrelation();
        virtual ~FrameCorrelation();

    public:
        std::map<std::string, std::string> toMap() const override;

    private:
        void setDataFromMap(const std::map<std::string, std::string>& map) override;

    private:
        Recording* video;
        Recording* simulation;
        Sequence videoSequence;
        Sequence simulationSequence;
    };

} // namespace NoiseSimulation

