#include "lanedetector.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace FeatureSetCreation {

  LaneDetector::LaneDetector(const LaneDetectionSettings& settings)
    : settings(settings) {
  }

  LaneDetector::~LaneDetector() {
  }

  std::vector<cv::Vec4i> LaneDetector::detectLanes(const cv::Mat& image) {
    cv::Mat cannyImage;
    cv::Canny(image, cannyImage, settings.firstThreshold, settings.secondThreshold, settings.apertureSize);

    //cv::imshow("Canny Image", cannyImage);
    //cv::waitKey();

    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(cannyImage, lines, settings.rho, settings.theta, settings.voteThreshold, settings.minLineLength, settings.maxLineGap);
    return lines;
  }

} // namespace FeatureSetCreation
