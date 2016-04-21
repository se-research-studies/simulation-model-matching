#pragma once

#include <cstdint>

namespace FeatureExtraction {

  struct Coordinates
  {
    Coordinates() = default;
    Coordinates(uint32_t x, uint32_t y);

    uint32_t x = 0;
    uint32_t y = 0;
  };

} // namespace FeatureExtraction

