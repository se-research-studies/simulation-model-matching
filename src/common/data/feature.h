#pragma once

#include <cstdint>

#include <FeatureSimulationCommon/Data/Coordinates>

namespace Common {

  struct Feature
  {
    Feature(const Coordinates& coordinates, uint32_t radius);

    const Coordinates coordinates;
    const uint32_t radius = 0;
  };

} // namespace FeatureExtraction

