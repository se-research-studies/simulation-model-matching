#include "feature.h"

#include <sstream>

#include <FeatureSimulation/Common/Utils>

namespace Common {

  Feature::Feature(uint32_t x, uint32_t y, float radius)
    : coordinates({ x, y }), diameter(radius) {
  }

  uint32_t Feature::getX() const {
    return coordinates.getX();
  }

  uint32_t Feature::getY() const {
    return coordinates.getY();
  }

  float Feature::getDiameter() const {
    return diameter;
  }

  std::string Feature::toSqlString() const {
    return "{" + std::to_string(coordinates.getX()) + "," + std::to_string(coordinates.getY()) + "," + std::to_string(diameter) + "}";
  }

  Feature Feature::fromSqlString(const std::string& stringFormatted) {
    std::stringstream stream(Utils::removeBraces(stringFormatted));
    std::string x, y, radius;
    std::getline(stream, x, ',');
    std::getline(stream, y, ',');
    std::getline(stream, radius, ',');
    return Feature(Utils::stoui(x), Utils::stoui(y), std::stof(radius));
  }

} // namespace FeatureExtraction
