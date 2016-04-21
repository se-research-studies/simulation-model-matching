#include "correlation.h"

namespace FeatureExtraction {

  Correlation::Correlation(uint32_t startFrame, uint32_t endFrame, const Position& startPosition, const Position& endPosition)
    : startFrame(startFrame), endFrame(endFrame), startPosition(startPosition), endPosition(endPosition)
  {
  }

} // namespace FeatureExtraction
