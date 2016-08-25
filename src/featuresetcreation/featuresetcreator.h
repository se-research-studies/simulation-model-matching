#pragma once

#include <FeatureSimulation/Common/Data/featureset.h>
#include <FeatureSimulation/Common/DataManagement/featuresetdao.h>

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
    void saveFeatureSet(const Common::FeatureSet& featureSet) const;

private:
    const std::string recordingFile;
    const std::string id;

    std::unique_ptr<FeatureDetector> featureDetector;
    Common::FeatureSetDAO featureSetDao;
};

} // namespace FeatureCreation

