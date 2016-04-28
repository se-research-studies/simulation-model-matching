#include "featuredetector.h"

#include <opencv2/imgproc/imgproc.hpp>

#include <FeatureSimulation/Common/Utils>
#include <FeatureSimulation/Common/Data/Feature>

namespace FeatureSetCreation {

  FeatureDetector::FeatureDetector() {
  }

  FeatureDetector::~FeatureDetector() {
  }

  Common::DirtyFrame FeatureDetector::detectFeaturesORB(const cv::Mat& image, const OrbSettings& settings) {
    cv::Mat grayscale;
    //cv::cvtColor(image, grayscale, CV_BGR2GRAY);
    std::vector<cv::KeyPoint> keyPoints;
//    cv::ORB detector(settings.nFeatures, settings.scaleFactor, settings.nLevels, settings.edgeThreshold, settings.firstLevel, settings.WTA_K, settings.scoreType, settings.patchSize);
//    detector.detect(grayscale, keyPoints);
    cv::OrbFeatureDetector detector;
    detector.detect(grayscale, keyPoints);

    std::vector<Common::Feature> features;
    for (const cv::KeyPoint& keyPoint : keyPoints) {
      features.push_back(Common::Feature(Common::Utils::to<uint32_t>(keyPoint.pt.x), Common::Utils::to<uint32_t>(keyPoint.pt.y), keyPoint.size));
    }
    return Common::DirtyFrame(move(features));
  }

} // namespace FeatureSetCreation
