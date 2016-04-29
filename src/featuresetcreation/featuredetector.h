#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <FeatureSimulation/Common/Data/DirtyFrame>

namespace FeatureSetCreation {

  class FeatureDetector {
  protected:
    FeatureDetector(bool guiEnabled);

  public:
    virtual ~FeatureDetector();

  public:
    Common::DirtyFrame detectFeatures(const cv::Mat& image, const cv::Mat& mask);

  protected:
    virtual std::vector<cv::KeyPoint> findKeyPoints(const cv::Mat& image, const cv::Mat& mask) = 0;

  private:
    void subtractLanes(const cv::Mat& image, const std::vector<cv::KeyPoint>& keyPoints) const;
    void showKeyPoints(const cv::Mat& image, const std::vector<cv::KeyPoint>& keyPoints) const;
    Common::DirtyFrame convertToDirtyFrame(const std::vector<cv::KeyPoint>& keyPoints) const;

  private:
    bool guiEnabled = true;
  };

} // namespace FeatureSetCreation

