#pragma once

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>
#include <FeatureSimulation/FeatureSetCreation/Settings>

namespace FeatureSetCreation {

class FeatureDetectorORB : public FeatureDetector {
public:
    FeatureDetectorORB(const Settings& settings);
    virtual ~FeatureDetectorORB();

protected:
    std::vector<cv::KeyPoint> findKeyPoints(const cv::Mat& image, const cv::Mat& mask) override;

private:
    const OrbSettings settings;
};

} // namespace FeatureSetCreation

