#include "featureset_test.h"

#include <FeatureSimulation/Common/Data/DirtyFrame>
#include <FeatureSimulation/Common/Data/Feature>
#include <FeatureSimulation/Common/Data/FeatureSet>

TEST(FeatureSetTest, exhaustionTest) {
  int64_t memSize;
  FILE *f = fopen("/proc/self/statm", "r");
  fscanf(f, "%ld", &memSize);
  fclose (f);
  std::cout << "Memory at start: " << memSize << std::endl;

  Common::FeatureSet featureSet("");
  for (int i = 0; i < 10000; ++i) {
    Common::DirtyFrame frame;
    for (int j = 0; j < 10000; ++j) {
      frame.addFeature(Common::Feature(j, j, j));
    }
    featureSet.addFrame(i, std::move(frame));
  }
  f = fopen("/proc/self/statm", "r");
  fscanf(f, "%ld", &memSize);
  fclose (f);
  std::cout << "Memory after frame creation: " << memSize << std::endl;

  Common::FeatureSet featureSet2(std::move(featureSet));
  ASSERT_EQ(featureSet2.getFrameCount(), 10000);
  ASSERT_EQ(featureSet.getFrameCount(), 0);

  f = fopen("/proc/self/statm", "r");
  fscanf(f, "%ld", &memSize);
  fclose (f);
  std::cout << "Memory after move: " << memSize << std::endl;

  ASSERT_TRUE(true);
}
