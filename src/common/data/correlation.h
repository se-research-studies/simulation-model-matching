#pragma once

#include <cstdint>

#include <FeatureSimulationCommon/Data/Position>

namespace Common {

  struct Correlation
  {
    Correlation(uint32_t startFrame, uint32_t endFrame, const Position& startPosition, const Position& endPosition);

    const uint32_t startFrame = 0;
    const uint32_t endFrame = 0;
    const Position startPosition;
    const Position endPosition;
  };

} // namespace FeatureExtraction

