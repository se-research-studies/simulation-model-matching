#pragma once

#include <FeatureSimulation/Common/Data/FeatureSet>
#include <FeatureSimulation/Common/DataManagement/Cursor>
#include <FeatureSimulation/Common/DataManagement/TableField>

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
    FeatureSet load(const std::string& recordingName) const;
    FeatureSet load(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const;
    void save(const FeatureSet& featureSet) const;

  private:
    std::string selectionString(const std::string& recordingName) const;
    std::string selectionString(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const;
    FeatureSet toFeatureSet(const std::string& recordingName, Cursor& cursor) const;
    std::vector<TableField> toRow(const std::string& recordingName, const std::pair<const uint32_t, DirtyFrame>& frame) const;
  };

} // namespace FeatureExtraction

