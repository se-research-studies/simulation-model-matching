#pragma once

#include <cstdint>

#include <FeatureSimulationCommon/Data/Coordinates>

namespace Common {

  struct Position
  {
    Position(const Coordinates& coordinates, uint16_t theta);

    const Coordinates coordinates;
    const uint16_t theta = 0;
  };

} // namespace FeatureExtraction

