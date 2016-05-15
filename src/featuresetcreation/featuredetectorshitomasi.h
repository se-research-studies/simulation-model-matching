#pragma once

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>
#include <FeatureSimulation/FeatureSetCreation/Settings>

namespace FeatureSetCreation {

class FeatureDetectorShiTomasi : public FeatureDetector {
public:
    FeatureDetectorShiTomasi(const Settings& settings);
    virtual ~FeatureDetectorShiTomasi();

protected:
    std::vector<cv::KeyPoint> findKeyPoints(const cv::Mat& image, const cv::Mat& mask) override;

private:
    const ShiTomasiSettings settings;
};

} // namespace FeatureSetCreation

