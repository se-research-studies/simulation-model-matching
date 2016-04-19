#pragma once

#include <DataManagement/Coordinates>

namespace FeatureExtraction {

  struct Position
  {
    Coordinates coordinates;
    uint8_t theta = 0;
  };

} // namespace FeatureExtraction

