#pragma once

#include <cstdint>

namespace Common {

class Coordinates {
public:
    Coordinates(int x, int y);
    Coordinates() = default;
    Coordinates(const Coordinates&) = default;

public:
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);

    bool operator==(const Coordinates& other) const;
    bool operator!=(const Coordinates& other) const;
    Coordinates& operator=(const Coordinates& other) = default;

private:
    int x = 0;
    int y = 0;
};

} // namespace FeatureExtraction

