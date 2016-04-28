#pragma once

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>

namespace FeatureSetCreation {

  class FeatureDetectorORB : public FeatureDetector {
  public:
    FeatureDetectorORB();
    virtual ~FeatureDetectorORB();

  public:
    Common::Frame detectFeatures(const cv::Mat& image) override;
  };

} // namespace FeatureSetCreation

