#pragma once

#include <cstdint>
#include <string>

#include <FeatureSimulation/Common/Data/coordinates.h>

namespace Common {

class Position {
public:
    Position(int x, int y, uint16_t theta);

public:
    int getX() const;
    int getY() const;
    uint16_t getTheta() const;
    std::string toSqlString() const;
    static Position fromSqlString(const std::string& stringFormatted);

private:
    const Coordinates coordinates;
    const uint16_t theta = 0;
};

} // namespace FeatureExtraction

