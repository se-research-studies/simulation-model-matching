#include "coordinates.h"

namespace Common {

Coordinates::Coordinates(uint32_t x, uint32_t y)
    : x(x), y(y) {
}

uint32_t Coordinates::getX() const {
    return x;
}

uint32_t Coordinates::getY() const {
    return y;
}

} // namespace FeatureExtraction
