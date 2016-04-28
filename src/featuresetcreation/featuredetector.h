#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <FeatureSimulation/Common/Data/DirtyFrame>

namespace FeatureSetCreation {

  struct OrbSettings {
    int nFeatures = 500;
    float scaleFactor = 1.2f;
    int nLevels = 8;
    int edgeThreshold = 31;
    int firstLevel = 0;
    int WTA_K = 2;
    int scoreType = cv::ORB::HARRIS_SCORE;
    int patchSize = 31;
    int fastThreshold = 20;
  };

  class FeatureDetector {
  public:
    FeatureDetector();
    virtual ~FeatureDetector();

  public:
    Common::DirtyFrame detectFeaturesORB(const cv::Mat& image, const OrbSettings& settings);
  };

} // namespace FeatureSetCreation

