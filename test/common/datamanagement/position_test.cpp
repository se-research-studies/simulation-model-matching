#include "position_test.h"

#include <FeatureSimulationCommon/Data/Position>

TEST(PositionTest, toString) {
  Common::Position position({1, 2}, 3);
  ASSERT_EQ("{1,2,3}", position.toString());
}

TEST(PositionTest, fromString) {
  Common::Position position = Common::Position::fromString("{1,2,3}");
  ASSERT_EQ(1, position.getX());
  ASSERT_EQ(2, position.getY());
  ASSERT_EQ(3, position.getTheta());
}