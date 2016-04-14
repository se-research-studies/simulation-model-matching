#pragma once

#include <cstdint>

namespace NoiseSimulation {

    struct Point
    {
        Point() = default;
        Point(uint32_t x, uint32_t y);

        uint32_t x = 0;
        uint32_t y = 0;
    };

} // namespace NoiseSimulation

