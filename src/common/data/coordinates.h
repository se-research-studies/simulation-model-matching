#pragma once

#include <cstdint>

namespace Common {

class Coordinates {
public:
    Coordinates(uint32_t x, uint32_t y);

public:
    uint32_t getX() const;
    uint32_t getY() const;

private:
    const uint32_t x = 0;
    const uint32_t y = 0;
};

} // namespace FeatureExtraction

