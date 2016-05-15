#include "featuredetectorshitomasi.h"

namespace FeatureSetCreation {

FeatureDetectorShiTomasi::FeatureDetectorShiTomasi(const Settings& settings)
    : FeatureDetector(settings), settings(settings.shiTomasiSettings) {
}

FeatureDetectorShiTomasi::~FeatureDetectorShiTomasi() {
}

std::vector<cv::KeyPoint> FeatureDetectorShiTomasi::findKeyPoints(const cv::Mat& image, const cv::Mat& mask) {
    std::vector<cv::KeyPoint> keyPoints;

    cv::GoodFeaturesToTrackDetector detector(settings.maxCorners,
            settings.qualityLevel,
            settings.minDistance,
            settings.blockSize,
            settings.useHarris,
            settings.kFree);

    detector.detect(image, keyPoints, mask);
    return keyPoints;
}

} // namespace FeatureSetCreation
