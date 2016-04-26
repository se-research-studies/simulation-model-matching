#pragma once

#include <FeatureSimulationCommon/Data/FeatureSet>
#include <FeatureSimulationCommon/DataManagement/Cursor>
#include <FeatureSimulationCommon/DataManagement/TableField>

namespace Common {

  namespace FeatureSetsContract {
    static const std::string TABLENAME = "FeatureSets";
    static const std::string COL_RECORDINGNAME = "recordingName";
    static const std::string COL_FRAME = "frame";
    static const std::string COL_FEATURES = "features";
    static const uint8_t INDEX_RECORDINGFILENAME = 0;
    static const uint8_t INDEX_FRAME = 1;
    static const uint8_t INDEX_FEATURES = 2;
  }

  class FeatureSetDAO {
  public:
    FeatureSetDAO();
    virtual ~FeatureSetDAO();

  public:
    std::unique_ptr<FeatureSet> load(const std::string& recordingName) const;
    std::unique_ptr<FeatureSet> load(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const;
    void save(FeatureSet& featureSet) const;

  private:
    std::string selectionString(const std::string& recordingName) const;
    std::string selectionString(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const;
    std::unique_ptr<FeatureSet> toFeatureSet(const std::string& recordingName, Cursor& cursor) const;
    std::vector<TableField> toRow(const std::string& recordingName, const std::pair<const uint32_t, std::unique_ptr<Frame>>& frame) const;
  };

} // namespace FeatureExtraction

