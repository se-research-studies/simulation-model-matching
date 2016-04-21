#pragma once

#include <cstdint>

#include <Data/Coordinates>

namespace FeatureExtraction {

  struct Feature
  {
    Feature(const Coordinates& coordinates, uint32_t radius);

    const Coordinates coordinates;
    const uint32_t radius = 0;
  };

} // namespace FeatureExtraction

