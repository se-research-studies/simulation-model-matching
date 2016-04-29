#include "featuredetectororb.h"

namespace FeatureSetCreation {

  FeatureDetectorORB::FeatureDetectorORB(bool guiEnabled, int nFeatures, float scaleFactor, int nLevels, int edgeThreshold, int firstLevel,
                                         int WTA_K, int scoreType, int patchSize, int fastThreshold)
    : FeatureDetector(guiEnabled),
      nFeatures(nFeatures), scaleFactor(scaleFactor), nLevels(nLevels), edgeThreshold(edgeThreshold), firstLevel(firstLevel),
      WTA_K(WTA_K), scoreType(scoreType), patchSize(patchSize), fastThreshold(fastThreshold) {
  }

  FeatureDetectorORB::~FeatureDetectorORB() {
  }

  void FeatureDetectorORB::validateSettings() const {
    // See also: http://docs.opencv.org/2.4.12/modules/features2d/doc/feature_detection_and_description.html#orb-orb
    std::string errors;
    if (scaleFactor < 1.0f || scaleFactor > 2.0f) {
      errors += "scaleFactor must have a value between 1.0 and 2.0.\n";
    }
    if (firstLevel != 0) {
      errors += "firstLevel should be left 0.\n";
    }
    if (WTA_K < 2 || WTA_K > 4) {
      errors += "WTA_K must be either 2, 3 or 4.\n";
    }
    if (scoreType != cv::ORB::HARRIS_SCORE && scoreType != cv::ORB::FAST_SCORE) {
      errors += "scoreType must be either 0 (HARRIS_SCORE) or 1 (FAST_SCORE).\n";
    }
    if (errors.size() > 0) {
      throw std::runtime_error(errors);
    }
  }

  std::vector<cv::KeyPoint> FeatureDetectorORB::findKeyPoints(const cv::Mat& image, const cv::Mat& mask) {
    std::vector<cv::KeyPoint> keyPoints;
    cv::ORB detector(nFeatures, scaleFactor, nLevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize);
    detector.detect(image, keyPoints, mask);
    return keyPoints;
  }

} // namespace FeatureSetCreation
