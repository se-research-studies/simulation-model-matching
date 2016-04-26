#include "feature.h"

#include <sstream>

#include <FeatureSimulationCommon/Utils>

namespace Common {

  Feature::Feature(const Coordinates& coordinates, uint32_t radius)
    : coordinates(coordinates), radius(radius) {
  }

  std::string Feature::toString() const {
    return "{" + std::to_string(coordinates.x) + "," + std::to_string(coordinates.y) + "," + std::to_string(radius) + "}";
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
