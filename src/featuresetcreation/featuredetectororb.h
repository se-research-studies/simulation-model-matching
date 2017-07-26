#pragma once

#include <FeatureSimulation/FeatureSetCreation/featuredetector.h>
#include <FeatureSimulation/FeatureSetCreation/settings.h>

namespace FeatureSetCreation {

class FeatureDetectorORB : public FeatureDetector {
public:
    FeatureDetectorORB(const Settings& _settings);
    virtual ~FeatureDetectorORB();

protected:
    std::vector<cv::KeyPoint> findKeyPoints(const cv::Mat& image, const cv::Mat& mask) override;

private:
    const OrbSettings settings;
};

} // namespace FeatureSetCreation

