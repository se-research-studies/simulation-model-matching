#include "rectangle.h"

namespace Common {

    Rectangle::Rectangle(const Coordinates& _topLeft, const Coordinates& _bottomRight)
        : topLeft(_topLeft), bottomRight(_bottomRight) {
    }

    Coordinates Rectangle::getTopLeft() const
    {
        return topLeft;
    }

    void Rectangle::setTopLeft(const Coordinates& value)
    {
        topLeft = value;
    }

    Coordinates Rectangle::getBottomRight() const
    {
        return bottomRight;
    }

    void Rectangle::setBottomRight(const Coordinates& value)
    {
        bottomRight = value;
    }

    bool Rectangle::operator==(const Rectangle& other) const
    {
        return topLeft == other.topLeft && bottomRight == other.bottomRight;
    }

    bool Rectangle::operator!=(const Rectangle& other) const
    {
        return topLeft != other.topLeft || bottomRight != other.bottomRight;
    }
    
} // namespace Common
