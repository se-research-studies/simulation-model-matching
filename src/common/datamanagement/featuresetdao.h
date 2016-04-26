#pragma once

#include <FeatureSimulationCommon/Data/FeatureSet>
#include <FeatureSimulationCommon/DataManagement/Cursor>
#include <FeatureSimulationCommon/DataManagement/TableField>

namespace Common {

  namespace FeatureSetsContract {
    std::string TABLENAME = "FeatureSets";
    std::string COL_RECORDINGNAME = "recordingName";
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
    std::unique_ptr<FeatureSet> load(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame);
    void save(FeatureSet& featureSet);

  private:
    std::string selectionString(const std::string& recordingName) const;
    std::string selectionString(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const;
    std::unique_ptr<FeatureSet> toFeatureSet(const std::string& recordingName, Cursor& cursor) const;
    std::unique_ptr<Frame> currentRowToFrame(const Cursor& cursor) const;
    std::vector<TableField> toRow(const std::string& recordingName, const std::pair<const uint32_t, std::unique_ptr<Frame>>& frame) const;
  };

} // namespace FeatureExtraction

