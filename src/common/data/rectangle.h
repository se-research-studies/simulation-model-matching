#pragma once

#include <functional>

#include <FeatureSimulation/Common/utils.h>
#include <FeatureSimulation/Common/Data/coordinates.h>

namespace Common {

    class Rectangle {
    public:
        Rectangle() = default;
        Rectangle(const Coordinates& topLeft, const Coordinates& bottomRight);

    public:
        Coordinates getTopLeft() const;
        void setTopLeft(const Coordinates& value);
        Coordinates getBottomRight() const;
        void setBottomRight(const Coordinates& value);

        bool operator==(const Rectangle& other) const;
        bool operator!=(const Rectangle& other) const;
        Rectangle& operator=(const Rectangle& other) = default;

    private:
        Coordinates topLeft;
        Coordinates bottomRight;
    };

} // namespace Common

namespace std {
    template<> struct hash<Common::Rectangle> {
        size_t operator()(const Common::Rectangle& rectangle) const {
            size_t hash = std::hash<int>()(rectangle.getTopLeft().getX());
            hash = Common::Utils::hashCombine(hash, rectangle.getTopLeft().getY());
            hash = Common::Utils::hashCombine(hash, rectangle.getBottomRight().getX());
            hash = Common::Utils::hashCombine(hash, rectangle.getBottomRight().getY());
            return hash;
        }
    };
}

