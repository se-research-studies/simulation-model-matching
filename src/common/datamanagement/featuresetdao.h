#pragma once

#include <FeatureSimulationCommon/Data/FeatureSet>

namespace Common {

  namespace FeatureSetsContract {
    std::string TABLENAME = "FeatureSets";
    std::string COL_RECORDINGFILENAME = "recordingName";
    uint8_t INDEX_RECORDINGFILENAME = 0;
    std::string COL_FRAME = "frame";
    uint8_t INDEX_FRAME = 1;
    std::string COL_FEATURES = "features";
    uint8_t INDEX_FEATURES = 2;
  }

  class FeatureSetDAO {
  public:
    FeatureSetDAO();
    virtual ~FeatureSetDAO();

  public:
    std::unique_ptr<FeatureSet> load(const std::string& recordingName);
    void save(FeatureSet& featureSet);

  private:
    std::string selectionString(const std::string& recordingName) const;
  };

} // namespace FeatureExtraction

