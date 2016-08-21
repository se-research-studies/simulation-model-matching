#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <FeatureSimulation/Common/Data/dirtyframe.h>
#include <FeatureSimulation/FeatureSetCreation/lanemarkingfilter.h>

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
    Common::DirtyFrame convertToDirtyFrame(const std::vector<cv::KeyPoint>& keyPoints) const;

private:
    bool guiEnabled = true;
    uint16_t maxDistance;

private:
    LaneMarkingFilter laneDetector;
};

} // namespace FeatureSetCreation

