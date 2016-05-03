#include "featuredetector.h"

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/Common/Utils>
#include <FeatureSimulation/Common/Data/Feature>

namespace FeatureSetCreation {

  FeatureDetector::FeatureDetector(const Settings& settings)
    : guiEnabled(settings.guiEnabled), laneDetector(settings.laneDetectionSettings) {
  }

  FeatureDetector::~FeatureDetector() {
  }

  Common::DirtyFrame FeatureDetector::detectFeatures(const cv::Mat& image, const cv::Mat& mask) {
    std::vector<cv::KeyPoint> keyPoints = findKeyPoints(image, mask);
    std::vector<cv::Vec4i> lanes = laneDetector.detectLanes(image);
    std::vector<cv::KeyPoint> featureKeyPoints = subtractLanes(keyPoints, lanes);
    if (guiEnabled) {
      showResults(image, mask, featureKeyPoints, lanes);
    }
    return convertToDirtyFrame(featureKeyPoints);
  }

  std::vector<cv::KeyPoint> FeatureDetector::subtractLanes(const std::vector<cv::KeyPoint>& keyPoints, const std::vector<cv::Vec4i>& lanes) const {
    std::vector<cv::KeyPoint> features;
    for (int i = 0; i < keyPoints.size(); ++i) {
      bool hitByLane = false;
      for (const cv::Vec4i& lane : lanes) {
        cv::Vec4i keyPointToLane(lane[0], lane[1], keyPoints.at(i).pt.x, keyPoints.at(i).pt.y);
        cv::Vec4i doubleKeyPointToLane = 2 * keyPointToLane;
        float radiusSquared = (keyPoints.at(i).size / 2);
        radiusSquared *= radiusSquared;
        float a = lane.dot(lane);
        float b = doubleKeyPointToLane.dot(lane);
        float c = keyPointToLane.dot(keyPointToLane) - radiusSquared;
        float discriminant = b*b-4*a*c;
        if (discriminant >= 0) {
          hitByLane = true;
        }
      }
      if (!hitByLane) {
        features.push_back(keyPoints.at(i));
      }
    }
    return features;
  }

  void FeatureDetector::showResults(const cv::Mat& image, const cv::Mat& mask, const std::vector<cv::KeyPoint>& keyPoints, const std::vector<cv::Vec4i>& lanes) const {
    cv::Mat completedImage(image.size(), image.type(), cv::Scalar(255, 255, 255));
    image.copyTo(completedImage, mask);
    cv::drawKeypoints(completedImage, keyPoints, completedImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    for (const cv::Vec4i& line : lanes) {
      cv::line(completedImage, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0,0,255), 1, CV_AA);
    }
    cv::imshow("Analyzed Image", completedImage);
    cv::waitKey();
  }

  Common::DirtyFrame FeatureDetector::convertToDirtyFrame(const std::vector<cv::KeyPoint>& keyPoints) const {
    std::vector<Common::Feature> features;
    for (const cv::KeyPoint& keyPoint : keyPoints) {
      features.push_back(Common::Feature(Common::Utils::to<uint32_t>(keyPoint.pt.x), Common::Utils::to<uint32_t>(keyPoint.pt.y), keyPoint.size));
    }
    return Common::DirtyFrame(move(features));
  }

} // namespace FeatureSetCreation
