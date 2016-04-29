#pragma once

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>

namespace FeatureSetCreation {

  class FeatureDetectorORB : public FeatureDetector {
  public:
    FeatureDetectorORB(bool guiEnabled, int nFeatures, float scaleFactor, int nLevels, int edgeThreshold,
                       int firstLevel, int WTA_K, int scoreType, int patchSize, int fastThreshold);
    virtual ~FeatureDetectorORB();

  protected:
    std::vector<cv::KeyPoint> findKeyPoints(const cv::Mat& image, const cv::Mat& mask) override;

  private:
    const int nFeatures = 500;
    const float scaleFactor = 1.2f;
    const int nLevels = 8;
    const int edgeThreshold = 31;
    const int firstLevel = 0;
    const int WTA_K = 2;
    const int scoreType = cv::ORB::HARRIS_SCORE;
    const int patchSize = 31;
    const int fastThreshold = 20;
  };

} // namespace FeatureSetCreation

