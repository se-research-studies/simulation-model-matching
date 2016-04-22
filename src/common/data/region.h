#pragma once

#include <FeatureSimulationCommon/Data/Coordinates>

namespace Common {

  struct Region
  {
    Region(const Coordinates& topLeft, const Coordinates& topRight, const Coordinates& bottomLeft, const Coordinates& bottomRight);

    const Coordinates topLeft;
    const Coordinates topRight;
    const Coordinates bottomLeft;
    const Coordinates bottomRight;
  };

} // namespace FeatureExtraction

