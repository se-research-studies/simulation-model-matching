#include "position.h"

#include <sstream>

#include <FeatureSimulation/Common/Utils>

namespace Common {

  Position::Position(const Coordinates& coordinates, uint16_t theta)
    : coordinates(coordinates), theta(theta) {
  }

  uint32_t Position::getX() const {
    return coordinates.getX();
  }

  uint32_t Position::getY() const {
    return coordinates.getY();
  }

  uint16_t Position::getTheta() const {
    return theta;
  }

  std::string Position::toString() const {
    return "{" + std::to_string(coordinates.getX()) + "," + std::to_string(coordinates.getY()) + "," + std::to_string(theta) + "}";
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
