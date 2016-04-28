#include "correlation.h"

namespace Common {

  Correlation::Correlation(uint32_t startFrame, uint32_t endFrame, const Position& startPosition, const Position& endPosition)
    : startFrame(startFrame), endFrame(endFrame), startPosition(startPosition), endPosition(endPosition)
  {
  }
  
  Position Correlation::getEndPosition() const {
      return endPosition;
  }
  
  Position Correlation::getStartPosition() const {
      return startPosition;
  }
  
  uint32_t Correlation::getEndFrame() const {
      return endFrame;
  }
  
  uint32_t Correlation::getStartFrame() const {
      return startFrame;
  }
  
} // namespace FeatureExtraction
