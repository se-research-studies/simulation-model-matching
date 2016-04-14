#include "framecorrelation.h"

#include <NoiseSimulation/DataContracts>
#include <NoiseSimulation/Recording>

namespace NoiseSimulation {

    FrameCorrelation::FrameCorrelation()
    {
    }

    FrameCorrelation::~FrameCorrelation()
    {
    }

    std::map<std::string, std::string> FrameCorrelation::toMap() const
    {
        std::map<std::string, std::string> result;
        result.emplace(FrameCorrelationFields::videoFilename(), video->getFilename());
        result.emplace(FrameCorrelationFields::videoStart(), std::to_string(videoSequence.getStart()));
        result.emplace(FrameCorrelationFields::videoEnd(), std::to_string(videoSequence.getEnd()));
        result.emplace(FrameCorrelationFields::simulationFilename(), simulation->getFilename());
        result.emplace(FrameCorrelationFields::simulationStart(), std::to_string(simulationSequence.getStart()));
        result.emplace(FrameCorrelationFields::simulationEnd(), std::to_string(simulationSequence.getEnd()));
        return result;
    }

    void FrameCorrelation::setDataFromMap(const std::map<std::string, std::string>& map)
    {

    }

} // namespace NoiseSimulation
