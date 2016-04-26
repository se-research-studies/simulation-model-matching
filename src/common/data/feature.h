#pragma once

#include <cstdint>
#include <string>

#include <FeatureSimulationCommon/Data/Coordinates>

namespace Common {

  class Feature {
  public:
    Feature(const Coordinates& coordinates, uint32_t radius);

  public:
    std::string toString() const;
    static Feature fromString(const std::string& stringFormatted);

  public:
    const Coordinates coordinates;
    const uint32_t radius = 0;
  };

} // namespace FeatureExtraction

