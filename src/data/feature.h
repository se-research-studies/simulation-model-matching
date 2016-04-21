#pragma once

#include <DataManagement/Coordinates>

namespace FeatureExtraction {

  struct Feature
  {
    Coordinates coordinates;
    uint32_t radius = 0;
  };

} // namespace FeatureExtraction

