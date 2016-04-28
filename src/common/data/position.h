#pragma once

#include <cstdint>
#include <string>

#include <FeatureSimulationCommon/Data/Coordinates>

namespace Common {

  class Position {
  public:
    Position(const Coordinates& coordinates, uint16_t theta);

  public:
    uint32_t getX() const;
    uint32_t getY() const;
    uint16_t getTheta() const;
    std::string toString() const;
    static Position fromString(const std::string& stringFormatted);

  private:
    const Coordinates coordinates;
    const uint16_t theta = 0;
  };

} // namespace FeatureExtraction

