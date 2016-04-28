#include "region.h"

namespace Common {

  Region::Region(const Coordinates& topLeft, const Coordinates& topRight, const Coordinates& bottomLeft, const Coordinates& bottomRight)
      : topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight)
  {
  }
  
  Coordinates Region::getTopLeft() const {
      return topLeft;
  }
  
  Coordinates Region::getTopRight() const {
      return topRight;
  }
  
  Coordinates Region::getBottomLeft() const {
      return bottomLeft;
  }
  
  Coordinates Region::getBottomRight() const {
      return bottomRight;
  }
  
} // namespace FeatureExtraction
