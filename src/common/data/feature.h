#pragma once

#include <cstdint>
#include <string>

#include <FeatureSimulation/Common/Data/Coordinates>

namespace Common {

  class Feature {
  public:
    Feature(uint32_t x, uint32_t y, float diameter);

  public:
    uint32_t getX() const;
    uint32_t getY() const;
    float getDiameter() const;
    std::string toSqlString() const;
    static Feature fromSqlString(const std::string& stringFormatted);

  private:
    const Coordinates coordinates;
    const float diameter = 0;
  };

} // namespace FeatureExtraction

