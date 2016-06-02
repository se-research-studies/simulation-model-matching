#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <FeatureSimulation/Common/Data/dirtyframe.h>
#include <FeatureSimulation/FeatureSetCreation/lanedetector.h>

namespace FeatureSetCreation {

class FeatureDetector {
protected:
    FeatureDetector(const Settings& settings);

public:
    virtual ~FeatureDetector();

public:
    Common::DirtyFrame detectFeatures(const cv::Mat& image, const cv::Mat& mask);

protected:
    virtual std::vector<cv::KeyPoint> findKeyPoints(const cv::Mat& image, const cv::Mat& mask) = 0;

private:
    std::vector<cv::KeyPoint> subtractLanes(const std::vector<cv::KeyPoint>& keyPoints, const std::vector<cv::Vec4i>& lanes) const;
    float pointDistanceSquared(float a1, float a2, float b1, float b2) const;
    float pointDistance(float a1, float a2, float b1, float b2) const;
    float dotProduct(float a1, float a2, float b1, float b2) const;
    void showResults(const cv::Mat& image, const cv::Mat& mask, const std::vector<cv::KeyPoint>& keyPoints, const std::vector<cv::Vec4i>& lanes) const;
    Common::DirtyFrame convertToDirtyFrame(const std::vector<cv::KeyPoint>& keyPoints) const;

private:
    bool guiEnabled = true;
    float fuzzinessFactor;

private:
    LaneDetector laneDetector;
};

} // namespace FeatureSetCreation

