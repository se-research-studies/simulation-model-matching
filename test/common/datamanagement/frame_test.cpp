#include "frame_test.h"

#include <FeatureSimulationCommon/Data/Feature>
#include <FeatureSimulationCommon/Data/Frame>

TEST(FrameTest, toString) {
  Common::Frame frame;
  frame.addFeature(Common::Feature({1, 2}, 3));
  frame.addFeature(Common::Feature({4, 5}, 6));
  ASSERT_EQ("{1,2,3};{4,5,6}", frame.toString());
}

TEST(FrameTest, fromString) {
  Common::Frame frame = Common::Frame::fromString("{1,2,3};{4,5,6}");
  ASSERT_EQ(2, frame.getFeatureCount());
  ASSERT_EQ(1, frame.getFeatures().at(0).getX());
  ASSERT_EQ(2, frame.getFeatures().at(0).getY());
  ASSERT_EQ(3, frame.getFeatures().at(0).getRadius());
  ASSERT_EQ(4, frame.getFeatures().at(1).getX());
  ASSERT_EQ(5, frame.getFeatures().at(1).getY());
  ASSERT_EQ(6, frame.getFeatures().at(1).getRadius());
}
