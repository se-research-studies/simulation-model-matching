#include "feature_test.h"

#include <FeatureSimulationCommon/Data/Feature>

TEST(FeatureTest, toString) {
  Common::Feature feature({1, 2}, 3);
  ASSERT_EQ("{1,2,3}", feature.toString());
}

TEST(FeatureTest, fromString) {
  Common::Feature feature = Common::Feature::fromString("{1,2,3}");
  ASSERT_EQ(1, feature.getX());
  ASSERT_EQ(2, feature.getY());
  ASSERT_EQ(3, feature.getRadius());
}
