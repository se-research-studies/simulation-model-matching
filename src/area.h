#pragma once

#include <NoiseSimulation/Loadable>
#include <NoiseSimulation/Point>

namespace NoiseSimulation {

    struct Area : public Loadable
    {
        Area(const Point& topLeft, const Point& topRight, const Point& bottomLeft, const Point& bottomRight);

        Point topLeft;
        Point topRight;
        Point bottomLeft;
        Point bottomRight;
    };

} // namespace NoiseSimulation

