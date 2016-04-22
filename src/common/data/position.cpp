#include "position.h"

namespace Common {

  Position::Position(const Coordinates& coordinates, uint16_t theta)
    : coordinates(coordinates), theta(theta)
  {
  }

} // namespace FeatureExtraction
