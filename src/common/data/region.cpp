#include "region.h"

namespace Common {

  Region::Region(const Coordinates& topLeft, const Coordinates& topRight, const Coordinates& bottomLeft, const Coordinates& bottomRight)
      : topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight)
  {
  }

} // namespace FeatureExtraction
