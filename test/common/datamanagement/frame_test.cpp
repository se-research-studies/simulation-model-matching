#include "frame_test.h"

#include <FeatureSimulationCommon/Data/Feature>
#include <FeatureSimulationCommon/Data/Frame>

TEST(FrameTest, toString) {
  Common::Frame frame;
  frame.features.push_back(Common::Feature({1, 2}, 3));
  frame.features.push_back(Common::Feature({4, 5}, 6));
  ASSERT_EQ("{1,2,3};{4,5,6}", frame.toString());
}

TEST(FrameTest, fromString) {
  std::unique_ptr<Common::Frame> frame = Common::Frame::fromString("{1,2,3};{4,5,6}");
  ASSERT_EQ(2, frame->features.size());
  ASSERT_EQ(1, frame->features.at(0).coordinates.x);
  ASSERT_EQ(2, frame->features.at(0).coordinates.y);
  ASSERT_EQ(3, frame->features.at(0).radius);
  ASSERT_EQ(4, frame->features.at(1).coordinates.x);
  ASSERT_EQ(5, frame->features.at(1).coordinates.y);
  ASSERT_EQ(6, frame->features.at(1).radius);
}
