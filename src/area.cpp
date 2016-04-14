#include "area.h"

namespace NoiseSimulation {

    Area::Area(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight)
        : topLeft(topLeft), topRight(topRight), bottomLeft(bottomLeft), bottomRight(bottomRight)
    {
    }

} // namespace NoiseSimulation
