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

  std::vector<cv::KeyPoint> FeatureDetectorORB::findKeyPoints(const cv::Mat& image, const cv::Mat& mask) {
    std::vector<cv::KeyPoint> keyPoints;
    cv::ORB detector(nFeatures, scaleFactor, nLevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize);
    detector.detect(image, keyPoints, mask);
    return keyPoints;
  }

} // namespace FeatureSetCreation
