#pragma once

#include <vector>
#include <opencv2/core/core.hpp>

#include <FeatureSimulation/FeatureSetCreation/Settings>

namespace FeatureSetCreation {

class LaneDetector {
public:
    LaneDetector(const LaneDetectionSettings& settings);
    virtual ~LaneDetector();

public:
    std::vector<cv::Vec4i> detectLanes(const cv::Mat& image);

private:
    const LaneDetectionSettings settings;
};

} // namespace FeatureSetCreation

