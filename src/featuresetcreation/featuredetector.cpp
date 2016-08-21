#include "featuredetector.h"

#include <FeatureSimulation/Common/utils.h>
#include <FeatureSimulation/Common/Data/feature.h>

#include <FeatureSimulation/FeatureSetCreation/guicontroler.h>

namespace FeatureSetCreation {

    FeatureDetector::FeatureDetector(const Settings& settings)
        : guiEnabled(settings.guiEnabled), maxDistance(settings.laneMarkingDetectionSettings.maxDistance), laneDetector(settings.laneMarkingDetectionSettings) {
    }

    FeatureDetector::~FeatureDetector() {
    }

    Common::DirtyFrame FeatureDetector::detectFeatures(const cv::Mat& image, const cv::Mat& mask) {
        std::vector<cv::KeyPoint> keyPoints = findKeyPoints(image, mask);
        keyPoints = laneDetector.filterOutLaneMarkings(image, keyPoints);
        GuiController::instance().setKeyPoints(keyPoints);
        return convertToDirtyFrame(keyPoints);
    }

    Common::DirtyFrame FeatureDetector::convertToDirtyFrame(const std::vector<cv::KeyPoint>& keyPoints) const {
        std::vector<Common::Feature> features;
        for (const cv::KeyPoint& keyPoint : keyPoints) {
            features.push_back(Common::Feature(Common::Utils::to<uint32_t>(keyPoint.pt.x), Common::Utils::to<uint32_t>(keyPoint.pt.y), keyPoint.size));
        }
        return Common::DirtyFrame(move(features));
    }

} // namespace FeatureSetCreation
