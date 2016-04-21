#pragma once

#include <cstdint>

namespace FeatureExtraction {

  struct Coordinates
  {
    Coordinates(uint32_t x, uint32_t y);

    const uint32_t x = 0;
    const uint32_t y = 0;
  };

} // namespace FeatureExtraction

