#pragma once

#include <FeatureSimulation/Common/Data/coordinates.h>

namespace Common {

class Region {
public:
    Region(const Coordinates& _topLeft, const Coordinates& _topRight, const Coordinates& _bottomLeft, const Coordinates& _bottomRight);

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

