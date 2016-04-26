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
    std::unique_ptr<FeatureSet> result = std::make_unique<FeatureSet>(recordingName);
    while (cursor.moveToNext()) {
      uint16_t index = cursor.getUShort(FeatureSetsContract::INDEX_FRAME);
      std::unique_ptr<Frame> frame = Frame::fromString(cursor.getString(FeatureSetsContract::INDEX_FEATURES));
      result->addFrame(index, move(frame));
    }
    Database::getInstance().endTransaction();
    return result;
  }

  void FeatureSetDAO::save(FeatureSet& featureSet) {
    Database::getInstance().beginTransaction();
    for (auto frame = featureSet.getFrames().cbegin(); frame != featureSet.getFrames().cend(); ++frame) {
      std::vector<TableField> row;
      row.push_back({FeatureSetsContract::COL_RECORDINGFILENAME, featureSet.getRecordingName()});
      row.push_back({FeatureSetsContract::COL_FRAME, std::to_string((*frame).first)});
      row.push_back({FeatureSetsContract::COL_FEATURES, (*frame).second->toString()});
      Database::getInstance().insert(FeatureSetsContract::TABLENAME, row);
    }
    Database::getInstance().endTransaction();
  }

  std::string FeatureSetDAO::selectionString(const std::string& recordingName) const {
    return FeatureSetsContract::COL_RECORDINGFILENAME + " = '" + recordingName + "'";
  }

} // namespace FeatureExtraction
