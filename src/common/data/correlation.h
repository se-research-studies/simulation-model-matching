#pragma once

#include <cstdint>

#include <FeatureSimulationCommon/Data/Position>

namespace Common {

  class Correlation {
  public:
    Correlation(uint32_t startFrame, uint32_t endFrame, const Position& startPosition, const Position& endPosition);

  public:
    uint32_t getStartFrame() const;
    uint32_t getEndFrame() const;
    Position getStartPosition() const;
    Position getEndPosition() const;

  private:
    const uint32_t startFrame = 0;
    const uint32_t endFrame = 0;
    const Position startPosition;
    const Position endPosition;
  };

} // namespace FeatureExtraction

