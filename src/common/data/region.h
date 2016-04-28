#pragma once

#include <FeatureSimulationCommon/Data/Coordinates>

namespace Common {

  class Region {
  public:
    Region(const Coordinates& topLeft, const Coordinates& topRight, const Coordinates& bottomLeft, const Coordinates& bottomRight);

  public:
    Coordinates getTopLeft() const;
    Coordinates getTopRight() const;
    Coordinates getBottomLeft() const;
    Coordinates getBottomRight() const;

  private:
    const Coordinates topLeft;
    const Coordinates topRight;
    const Coordinates bottomLeft;
    const Coordinates bottomRight;
  };

} // namespace FeatureExtraction

