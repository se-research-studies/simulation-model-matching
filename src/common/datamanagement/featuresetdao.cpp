#include "featuresetdao.h"

#include <FeatureSimulationCommon/MakeUnique>
#include <FeatureSimulationCommon/DataManagement/Database>

namespace Common {

  FeatureSetDAO::FeatureSetDAO() {
  }

  FeatureSetDAO::~FeatureSetDAO() {
  }

  std::unique_ptr<FeatureSet> FeatureSetDAO::load(const std::string& recordingName) {
    Database::getInstance().beginTransaction();
    Cursor cursor = Database::getInstance().query(FeatureSetsContract::TABLENAME, {"*"}, selectionString(recordingName));
    std::unique_ptr<FeatureSet> result = toFeatureSet(recordingName, cursor);
    Database::getInstance().endTransaction();
    return result;
  }

  std::unique_ptr<FeatureSet> FeatureSetDAO::load(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) {
    Database::getInstance().beginTransaction();
    Cursor cursor = Database::getInstance().query(FeatureSetsContract::TABLENAME, {"*"}, selectionString(recordingName, startFrame, endFrame));
    std::unique_ptr<FeatureSet> result = toFeatureSet(recordingName, cursor);
    Database::getInstance().endTransaction();
    return result;
  }

  std::string FeatureSetDAO::selectionString(const std::string& recordingName) const {
    return FeatureSetsContract::COL_RECORDINGNAME + " = '" + recordingName + "'";
  }

  std::string FeatureSetDAO::selectionString(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const {
    return FeatureSetsContract::COL_RECORDINGNAME + " = '" + recordingName + "' " +
        "AND " + FeatureSetsContract::COL_FRAME + " BETWEEN " + std::to_string(startFrame) + " AND " + std::to_string(endFrame);
  }

  std::unique_ptr<FeatureSet> FeatureSetDAO::toFeatureSet(const std::string& recordingName, Cursor& cursor) const {
    std::unique_ptr<FeatureSet> result = std::make_unique<FeatureSet>(recordingName);
    while (cursor.moveToNext()) {
      result->addFrame(cursor.getUShort(FeatureSetsContract::INDEX_FRAME), currentRowToFrame(cursor));
    }
    return result;
  }

  std::unique_ptr<Frame> FeatureSetDAO::currentRowToFrame(const Cursor& cursor) const {
    std::string features = cursor.getString(FeatureSetsContract::INDEX_FEATURES);
    return Frame::fromString(features);
  }

  void FeatureSetDAO::save(FeatureSet& featureSet) {
    Database::getInstance().beginTransaction();
    for (auto frame = featureSet.getFrames().cbegin(); frame != featureSet.getFrames().cend(); ++frame) {
      Database::getInstance().insert(FeatureSetsContract::TABLENAME, toRow(featureSet.getRecordingName(), *frame));
    }
    Database::getInstance().endTransaction();
  }

  std::vector<TableField> FeatureSetDAO::toRow(const std::string& recordingName, const std::pair<const uint32_t, std::unique_ptr<Frame>>& frame) const {
    std::vector<TableField> result;
    result.push_back({FeatureSetsContract::COL_RECORDINGNAME, recordingName});
    result.push_back({FeatureSetsContract::COL_FRAME, std::to_string(frame.first)});
    result.push_back({FeatureSetsContract::COL_FEATURES, frame.second->toString()});
    return result;
  }

} // namespace FeatureExtraction
