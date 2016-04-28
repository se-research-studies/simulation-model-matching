#include "featuresetdao.h"

#include <FeatureSimulationCommon/MakeUnique>
#include <FeatureSimulationCommon/DataManagement/Database>

namespace Common {

  FeatureSetDAO::FeatureSetDAO() {
  }

  FeatureSetDAO::~FeatureSetDAO() {
  }

  FeatureSet FeatureSetDAO::load(const std::string& recordingName) const {
    Cursor cursor = Database::getInstance().query(FeatureSetsContract::TABLENAME, {"*"}, selectionString(recordingName));
    return toFeatureSet(recordingName, cursor);
  }

  FeatureSet FeatureSetDAO::load(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const {
    Cursor cursor = Database::getInstance().query(FeatureSetsContract::TABLENAME, {"*"}, selectionString(recordingName, startFrame, endFrame));
    return toFeatureSet(recordingName, cursor);
  }

  std::string FeatureSetDAO::selectionString(const std::string& recordingName) const {
    return FeatureSetsContract::COL_RECORDINGNAME + " = '" + recordingName + "'";
  }

  std::string FeatureSetDAO::selectionString(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const {
    return FeatureSetsContract::COL_RECORDINGNAME + " = '" + recordingName + "' " +
        "AND " + FeatureSetsContract::COL_FRAME + " BETWEEN " + std::to_string(startFrame) + " AND " + std::to_string(endFrame);
  }

  FeatureSet FeatureSetDAO::toFeatureSet(const std::string& recordingName, Cursor& cursor) const {
    FeatureSet result(recordingName);
    while (cursor.moveToNext()) {
      std::string features = cursor.getString(FeatureSetsContract::INDEX_FEATURES);
      result.addFrame(cursor.getUShort(FeatureSetsContract::INDEX_FRAME), Frame::fromString(features));
    }
    return result;
  }

  void FeatureSetDAO::save(const FeatureSet& featureSet) const {
    for (auto frame = featureSet.getFrames().cbegin(); frame != featureSet.getFrames().cend(); ++frame) {
      Database::getInstance().insert(FeatureSetsContract::TABLENAME, toRow(featureSet.getRecordingName(), *frame));
    }
  }

  std::vector<TableField> FeatureSetDAO::toRow(const std::string& recordingName, const std::pair<const uint32_t, Frame>& frame) const {
    std::vector<TableField> result;
    result.push_back({FeatureSetsContract::COL_RECORDINGNAME, recordingName});
    result.push_back({FeatureSetsContract::COL_FRAME, std::to_string(frame.first)});
    result.push_back({FeatureSetsContract::COL_FEATURES, frame.second.toString()});
    return result;
  }

} // namespace FeatureExtraction
