#include "featureset_test.h"

#include <FeatureSimulation/Common/Data/DirtyFrame>
#include <FeatureSimulation/Common/Data/Feature>
#include <FeatureSimulation/Common/Data/FeatureSet>

TEST(FeatureSetTest, stackOverflowTest) {
  int64_t memSize;
  FILE *f = fopen("/proc/self/statm", "r");
  fscanf(f, "%ld", &memSize);
  fclose (f);
  std::cout << "Memory before: " << memSize << std::endl;

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
  std::cout << "Memory after: " << memSize << std::endl;

  ASSERT_TRUE(true);
}
