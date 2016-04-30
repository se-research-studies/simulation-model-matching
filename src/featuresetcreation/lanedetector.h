#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

namespace FeatureSetCreation {

  class LaneDetector {
  public:
    LaneDetector();
    virtual ~LaneDetector();

  public:
    std::vector<cv::Vec4i> detectLanes(const cv::Mat& image);
  };

} // namespace FeatureSetCreation

