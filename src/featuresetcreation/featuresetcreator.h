#pragma once

#include <FeatureSimulation/Common/Data/featureset.h>
#include <FeatureSimulation/Common/DataManagement/featuresetdao.h>
#include <FeatureSimulation/Common/DataManagement/ronidao.h>

#include <FeatureSimulation/FeatureSetCreation/featuredetector.h>
#include <FeatureSimulation/FeatureSetCreation/featuredetectororb.h>
#include <FeatureSimulation/FeatureSetCreation/featuredetectorshitomasi.h>

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

