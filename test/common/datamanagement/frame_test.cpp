#include "frame_test.h"

#include <FeatureSimulation/Common/Data/DirtyFrame>
#include <FeatureSimulation/Common/Data/Feature>

TEST(FrameTest, toString) {
    Common::DirtyFrame frame;
    frame.addFeature(Common::Feature(1, 2, 3));
    frame.addFeature(Common::Feature(4, 5, 6));
    ASSERT_EQ("{1,2,3.000000};{4,5,6.000000}", frame.toSqlString());
}

TEST(FrameTest, fromString) {
    Common::DirtyFrame frame = Common::DirtyFrame::fromSqlString("{1,2,3};{4,5,6}");
    ASSERT_EQ(2, frame.getFeatureCount());
    ASSERT_EQ(1, frame.getFeatures().at(0).getX());
    ASSERT_EQ(2, frame.getFeatures().at(0).getY());
    ASSERT_EQ(3, frame.getFeatures().at(0).getDiameter());
    ASSERT_EQ(4, frame.getFeatures().at(1).getX());
    ASSERT_EQ(5, frame.getFeatures().at(1).getY());
    ASSERT_EQ(6, frame.getFeatures().at(1).getDiameter());
}

TEST(FrameTest, stackOverflowTest) {
    Common::DirtyFrame frame;
    for (int i = 0; i < 1000000; ++i) {
        frame.addFeature(Common::Feature(i, i, i));
    }
    ASSERT_TRUE(true);
}
