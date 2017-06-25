#include "region.h"

namespace Common {

Region::Region(const Coordinates& _topLeft, const Coordinates& _topRight, const Coordinates& _bottomLeft, const Coordinates& _bottomRight)
    : topLeft(_topLeft), topRight(_topRight), bottomLeft(_bottomLeft), bottomRight(_bottomRight)
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
