#include "lanedetector.h"

#include <opencv2/imgproc/imgproc.hpp>

namespace FeatureSetCreation {

  LaneDetector::LaneDetector()
  {
  }

  LaneDetector::~LaneDetector()
  {
  }

  std::vector<cv::Vec4i> LaneDetector::detectLanes(const cv::Mat& image) {
    cv::Mat dst, cdst;
    cv::Canny(image, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);


//    std::vector<cv::Vec2f> lines;
//    cv::HoughLines(dst, lines, 1, CV_PI/180, 100, 50, 50);

//    for( size_t i = 0; i < lines.size(); i++) {
//      float rho = lines[i][0], theta = lines[i][1];
//      cv::Point pt1, pt2;
//      double a = cos(theta), b = sin(theta);
//      double x0 = a*rho, y0 = b*rho;
//      pt1.x = cvRound(x0 + 1000*(-b));
//      pt1.y = cvRound(y0 + 1000*(a));
//      pt2.x = cvRound(x0 - 1000*(-b));
//      pt2.y = cvRound(y0 - 1000*(a));
//      cv::line( cdst, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);
//    }

    std::vector<cv::Vec4i> lines;
      cv::HoughLinesP(dst, lines, 1, CV_PI/180, 50, 30, 20);
      for( size_t i = 0; i < lines.size(); i++ )
      {
        cv::Vec4i l = lines[i];
        cv::line( cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
      }
      return lines;
  }

} // namespace FeatureSetCreation
