#include "settingsvalidator.h"

namespace FeatureSetCreation {

SettingsValidator::SettingsValidator() {
}

SettingsValidator::~SettingsValidator() {
}

void SettingsValidator::validate(const Settings& settings) const {
    std::string errors;
    if (settings.detectionAlg != "ORB" && settings.detectionAlg != "ShiTomasi") {
        errors += settings.detectionAlg + " is not a supported feature detection algorithm.\n";
    }
    errors += validateOrbSettings(settings.orbSettings);
    errors += validateLaneDetectionSettings(settings.laneMarkingDetectionSettings);
    if (errors.size() > 0) {
        throw std::runtime_error(errors);
    }
}

std::string SettingsValidator::validateOrbSettings(const OrbSettings& settings) const {
    // See also: http://docs.opencv.org/2.4.12/modules/features2d/doc/feature_detection_and_description.html#orb-orb
    std::string errors;
    if (settings.scaleFactor < 1.0f || settings.scaleFactor > 2.0f) {
        errors += "scaleFactor must have a value between 1.0 and 2.0.\n";
    }
    if (settings.firstLevel != 0) {
        errors += "firstLevel should be left 0.\n";
    }
    if (settings.WTA_K < 2 || settings.WTA_K > 4) {
        errors += "WTA_K must be either 2, 3 or 4.\n";
    }
    if (settings.scoreType != cv::ORB::HARRIS_SCORE && settings.scoreType != cv::ORB::FAST_SCORE) {
        errors += "scoreType must be either 0 (HARRIS_SCORE) or 1 (FAST_SCORE).\n";
    }
    return errors;
}

std::string SettingsValidator::validateLaneDetectionSettings(const LaneMarkingFilterSettings& settings) const {
    // See also: http://docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=houghlinesp#houghlinesp
    std::string errors;
    if (settings.apertureSize != 3 && settings.apertureSize != 5 && settings.apertureSize != 7) {
        errors += "apertureSize must be either 3, 5 or 7.\n";
    }
    return errors;
}

} // namespace FeatureSetCreation
