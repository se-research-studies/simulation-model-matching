#include "featuredetectororb.h"

namespace FeatureSetCreation {

  FeatureDetectorORB::FeatureDetectorORB(const Settings& settings)
    : FeatureDetector(settings), settings(settings.orbSettings) {
  }

  FeatureDetectorORB::~FeatureDetectorORB() {
  }

  std::vector<cv::KeyPoint> FeatureDetectorORB::findKeyPoints(const cv::Mat& image, const cv::Mat& mask) {
    std::vector<cv::KeyPoint> keyPoints;
    cv::ORB detector(settings.nFeatures, settings.scaleFactor, settings.nLevels, settings.edgeThreshold, settings.firstLevel,
                     settings.WTA_K, settings.scoreType, settings.patchSize);
    detector.detect(image, keyPoints, mask);
    return keyPoints;
  }

} // namespace FeatureSetCreation
