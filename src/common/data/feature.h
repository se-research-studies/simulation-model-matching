#pragma once

#include <cstdint>
#include <string>

#include <FeatureSimulationCommon/Data/Coordinates>

namespace Common {

  class Feature {
  public:
    Feature(const Coordinates& coordinates, uint32_t radius);

  public:
    uint32_t getX() const;
    uint32_t getY() const;
    uint32_t getRadius() const;
    std::string toString() const;
    static Feature fromString(const std::string& stringFormatted);

  private:
    const Coordinates coordinates;
    const uint32_t radius = 0;
  };

} // namespace FeatureExtraction

