#pragma once

#include <DataManagement/Point>

namespace FeatureExtraction {

  struct Feature
  {
    Coordinates coordinates;
    uint32_t radius = 0;
  };

} // namespace FeatureExtraction

