#pragma once

#include <unordered_map>

#include <FeatureSimulation/Common/Data/featureset.h>
#include <FeatureSimulation/Common/Data/rectangle.h>
#include <FeatureSimulation/Common/Data/recordingsection.h>

namespace Common {

    typedef std::unordered_map<Common::Rectangle, std::unique_ptr<Common::FeatureSet>> LocalFeatureSets;
    typedef std::unordered_map<Common::Rectangle, Common::RecordingSection> LocalRecordingSections;

} // namespace Common

