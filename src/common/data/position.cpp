#include "position.h"

#include <sstream>

#include <FeatureSimulationCommon/Utils>

namespace Common {

  Position::Position(const Coordinates& coordinates, uint16_t theta)
    : coordinates(coordinates), theta(theta) {
  }

  std::string Position::toString() const {
    return "{" + std::to_string(coordinates.x) + "," + std::to_string(coordinates.y) + "," + std::to_string(theta) + "}";
  }

  Position Position::fromString(const std::string& stringFormatted) {
    std::stringstream stream(Utils::removeBraces(stringFormatted));
    std::string x, y, theta;
    std::getline(stream, x, ',');
    std::getline(stream, y, ',');
    std::getline(stream, theta, ',');
    return Position({Utils::stoui(x), Utils::stoui(y)}, Utils::stoui(theta));
  }

} // namespace FeatureExtraction
