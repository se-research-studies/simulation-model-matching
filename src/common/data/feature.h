#pragma once

#include <cstdint>
#include <string>

#include <FeatureSimulation/Common/Data/coordinates.h>

namespace Common {

class Feature {
public:
    Feature(int x, int y, uint16_t diameter);

public:
    int getX() const;
    int getY() const;
    uint16_t getDiameter() const;
    std::string toSqlString() const;
    static Feature fromSqlString(const std::string& stringFormatted);

private:
    const Coordinates coordinates;
    const uint16_t diameter = 0;
};

} // namespace FeatureExtraction

