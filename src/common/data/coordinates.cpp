#include "coordinates.h"

namespace Common {

Coordinates::Coordinates(int _x, int _y)
    : x(_x), y(_y) {
}

int Coordinates::getX() const {
    return x;
}

void Coordinates::setX(int value)
{
    x = value;
}

int Coordinates::getY() const {
    return y;
}

void Coordinates::setY(int value)
{
    y = value;
}

bool Coordinates::operator==(const Coordinates& other) const
{
    return x == other.x && y == other.y;
}

bool Coordinates::operator!=(const Coordinates& other) const
{
    return x != other.x || y != other.y;
}

} // namespace FeatureExtraction
