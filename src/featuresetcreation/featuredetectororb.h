#pragma once

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>

namespace FeatureSetCreation {

  class FeatureDetectorORB : public FeatureDetector {
  public:
    FeatureDetectorORB();
    virtual ~FeatureDetectorORB();
  };

} // namespace FeatureSetCreation

