#include "feature.h"

#include <sstream>

#include <FeatureSimulationCommon/Utils>

namespace Common {

  Feature::Feature(const Coordinates& coordinates, uint32_t radius)
    : coordinates(coordinates), radius(radius) {
  }

  uint32_t Feature::getX() const {
    return coordinates.getX();
  }

  uint32_t Feature::getY() const {
    return coordinates.getY();
  }

  uint32_t Feature::getRadius() const {
    return radius;
  }

  std::string Feature::toString() const {
    return "{" + std::to_string(coordinates.getX()) + "," + std::to_string(coordinates.getY()) + "," + std::to_string(radius) + "}";
  }

  Feature Feature::fromString(const std::string& stringFormatted) {
    std::stringstream stream(Utils::removeBraces(stringFormatted));
    std::string x, y, radius;
    std::getline(stream, x, ',');
    std::getline(stream, y, ',');
    std::getline(stream, radius, ',');
    return Feature({Utils::stoui(x), Utils::stoui(y)}, Utils::stoui(radius));
  }

} // namespace FeatureExtraction
