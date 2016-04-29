#include "featuredetector.h"

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/Common/Utils>
#include <FeatureSimulation/Common/Data/Feature>

namespace FeatureSetCreation {

  FeatureDetector::FeatureDetector() {
  }

  FeatureDetector::~FeatureDetector() {
  }

  Common::DirtyFrame FeatureDetector::detectFeaturesORB(const cv::Mat& image, const OrbSettings& settings) {

    cv::Mat imageToAnalyze = getAnalyzableImage(image);
    std::vector<cv::KeyPoint> keyPoints = findKeyPointsWithORB(image, settings);
    if (settings.guiEnabled) {
      showKeyPoints(image, keyPoints);
    }
    return convertToDirtyFrame(keyPoints);
  }

  cv::Mat FeatureDetector::getAnalyzableImage(const cv::Mat& sourceImage) const {
    if (isGrayscale(sourceImage)) {
      return sourceImage;
    } else {
      cv::Mat grayscaledImage;
      cv::cvtColor(sourceImage, grayscaledImage, CV_BGR2GRAY);
      return grayscaledImage;
    }
  }

  bool FeatureDetector::isGrayscale(const cv::Mat& image) const {
    return image.channels() == 1;
  }

  std::vector<cv::KeyPoint> FeatureDetector::findKeyPointsWithORB(const cv::Mat& image, const OrbSettings& settings) const {
    std::vector<cv::KeyPoint> keyPoints;
    cv::ORB detector(settings.nFeatures, settings.scaleFactor, settings.nLevels, settings.edgeThreshold, settings.firstLevel, settings.WTA_K, settings.scoreType, settings.patchSize);
    detector.detect(image, keyPoints);
    return keyPoints;
  }

  void FeatureDetector::showKeyPoints(const cv::Mat& image, const std::vector<cv::KeyPoint>& keyPoints) const {
    cv::Mat debugImage;
    cv::drawKeypoints(image, keyPoints, debugImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    cv::imshow("Keypoints", debugImage);
    cv::waitKey(50);
  }

  Common::DirtyFrame FeatureDetector::convertToDirtyFrame(const std::vector<cv::KeyPoint>& keyPoints) const {
    std::vector<Common::Feature> features;
    for (const cv::KeyPoint& keyPoint : keyPoints) {
      features.push_back(Common::Feature(Common::Utils::to<uint32_t>(keyPoint.pt.x), Common::Utils::to<uint32_t>(keyPoint.pt.y), keyPoint.size));
    }
    return Common::DirtyFrame(move(features));
  }

} // namespace FeatureSetCreation
