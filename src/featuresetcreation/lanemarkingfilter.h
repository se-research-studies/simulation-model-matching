#pragma once

#include <vector>

#include <opencv2/core/core.hpp>

#include <FeatureSimulation/FeatureSetCreation/settings.h>

namespace FeatureSetCreation {

class LaneMarkingFilter {
public:
    LaneMarkingFilter(const LaneMarkingFilterSettings& settings);
    virtual ~LaneMarkingFilter();

public:
    std::vector<cv::KeyPoint> filterOutLaneMarkings(const cv::Mat& image, const std::vector<cv::KeyPoint>& keyPoints);

private:
    std::vector<cv::Vec4i> detectLines(const cv::Mat& image);
    bool getsHitByLine(const cv::Point2f& point, const cv::Vec4i& line) const;
    float pointDistanceSquared(const cv::Point2f& a, const cv::Point2f& b) const;
    float pointDistance(const cv::Point2f& a, const cv::Point2f& b) const;
    cv::Point2f projectPointOntoLine(const cv::Point2f& p, const float lineLengthSquared, const cv::Point2f& lineStart, const cv::Point2f& lineEnd) const;

private:
    const LaneMarkingFilterSettings settings;
};

} // namespace FeatureSetCreation
