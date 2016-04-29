#include "featuredetector.h"

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/Common/Utils>
#include <FeatureSimulation/Common/Data/Feature>

namespace FeatureSetCreation {

  FeatureDetector::FeatureDetector(bool guiEnabled)
    : guiEnabled(guiEnabled) {
  }

  FeatureDetector::~FeatureDetector() {
  }

  Common::DirtyFrame FeatureDetector::detectFeatures(const cv::Mat& image, const cv::Mat& mask) {
    std::vector<cv::KeyPoint> keyPoints = findKeyPoints(image, mask);
    subtractLanes(image, keyPoints);
    if (guiEnabled) {
      showKeyPoints(image, keyPoints);
    }
    return convertToDirtyFrame(keyPoints);
  }

  void FeatureDetector::subtractLanes(const cv::Mat& image, const std::vector<cv::KeyPoint>& keyPoints) const
  {

  }

  void FeatureDetector::showKeyPoints(const cv::Mat& image, const std::vector<cv::KeyPoint>& keyPoints) const {
    cv::Mat imageWithKeypoints;
    cv::drawKeypoints(image, keyPoints, imageWithKeypoints, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    cv::imshow("Keypoints", imageWithKeypoints);
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
