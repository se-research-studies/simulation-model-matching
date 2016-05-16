#pragma once

#include <FeatureSimulation/Common/Data/FeatureSet>
#include <FeatureSimulation/Common/DataManagement/FeatureSetDAO>
#include <FeatureSimulation/Common/DataManagement/RoniDAO>

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>
#include <FeatureSimulation/FeatureSetCreation/FeatureDetectorORB>
#include <FeatureSimulation/FeatureSetCreation/FeatureDetectorShiTomasi>

namespace FeatureSetCreation {

class FeatureSetCreator {
public:
    FeatureSetCreator(const Settings& settings);
    virtual ~FeatureSetCreator();

public:
    void createFeatureSet();

private:
    cv::Mat createMaskFromRonis(const cv::Size& imageSize) const;
    std::vector<Common::Region> loadRonis() const;
    void saveFeatureSet(const Common::FeatureSet& featureSet) const;

private:
    std::string recordingFile;

    std::unique_ptr<FeatureDetector> featureDetector;
    Common::FeatureSetDAO featureSetDao;
    Common::RoniDAO roniDao;
};

} // namespace FeatureCreation

