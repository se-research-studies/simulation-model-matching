#pragma once

#include <Data/Coordinates>

namespace FeatureExtraction {

  struct Region
  {
    Region(const Coordinates& topLeft, const Coordinates& topRight, const Coordinates& bottomLeft, const Coordinates& bottomRight);

    const Coordinates topLeft;
    const Coordinates topRight;
    const Coordinates bottomLeft;
    const Coordinates bottomRight;
  };

} // namespace FeatureExtraction

