#pragma once

#include <cstdint>
#include <string>

#include <FeatureSimulation/Common/Data/Coordinates>

namespace Common {

  class Position {
  public:
    Position(uint32_t x, uint32_t y, uint16_t theta);

  public:
    uint32_t getX() const;
    uint32_t getY() const;
    uint16_t getTheta() const;
    std::string toSqlString() const;
    static Position fromSqlString(const std::string& stringFormatted);

  private:
    const Coordinates coordinates;
    const uint16_t theta = 0;
  };

} // namespace FeatureExtraction

