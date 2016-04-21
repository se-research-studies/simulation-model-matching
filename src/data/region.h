#pragma once

#include <DataManagement/Coordinates>

namespace FeatureExtraction {

  struct Region
  {
    Region(const Coordinates& topLeft, const Coordinates& topRight, const Coordinates& bottomLeft, const Coordinates& bottomRight);

    Coordinates topLeft;
    Coordinates topRight;
    Coordinates bottomLeft;
    Coordinates bottomRight;
  };

} // namespace FeatureExtraction

