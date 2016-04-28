#pragma once

#include <opencv2/core/core.hpp>

#include <FeatureSimulation/Common/Data/Frame>

namespace FeatureSetCreation {

  class FeatureDetector
  {
  public:
    FeatureDetector();
    virtual ~FeatureDetector();

  public:
    virtual Common::Frame detectFeatures(const cv::Mat& image) = 0;
  };

} // namespace FeatureSetCreation

