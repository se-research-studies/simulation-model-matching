#include "feature.h"

#include <sstream>

#include <FeatureSimulation/Common/utils.h>

namespace Common {

Feature::Feature(int x, int y, uint16_t radius)
    : coordinates({ x, y }), diameter(radius) {
}

int Feature::getX() const {
    return coordinates.getX();
}

int Feature::getY() const {
    return coordinates.getY();
}

uint16_t Feature::getDiameter() const {
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
    return Feature(std::stoi(x), std::stoi(y), Utils::stoi<uint16_t>(radius));
}

} // namespace FeatureExtraction
