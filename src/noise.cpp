#include "noise.h"

#include <utility>

#include <NoiseSimulation/DataContracts>
#include <NoiseSimulation/Frame>
#include <NoiseSimulation/Recording>

namespace NoiseSimulation {

    Noise::Noise()
    {
    }

    Noise::~Noise()
    {
    }

    std::map<std::string, std::string> Noise::toMap() const
    {
        std::map<std::string, std::string> result;
        result.emplace(NoiseFields::videoFilename(), frame->getRecording()->getFilename());
        result.emplace(NoiseFields::frameIndex(), std::to_string(frame->getIndex()));
        result.emplace(NoiseFields::x(), std::to_string(coordinates.x));
        result.emplace(NoiseFields::y(), std::to_string(coordinates.y));
        result.emplace(NoiseFields::radius(), std::to_string(radius));
        return result;
    }

    void Noise::setDataFromMap(const std::map<std::string, std::string>& map)
    {

    }

} // namespace NoiseSimulation
