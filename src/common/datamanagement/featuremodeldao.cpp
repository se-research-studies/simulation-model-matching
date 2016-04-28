#include "featuremodeldao.h"

#include <FeatureSimulation/Common/MakeUnique>
#include <FeatureSimulation/Common/DataManagement/Database>

namespace Common {

  FeatureModelDAO::FeatureModelDAO() {
  }

  FeatureModelDAO::~FeatureModelDAO() {
  }

  std::vector<FeatureModel> FeatureModelDAO::load(const std::string& simulationName) const {
    Cursor cursor = Database::getInstance().query(FeatureModelsContract::TABLENAME, {"*"}, selectionString(simulationName));
    return toFeatureModels(simulationName, cursor);
  }

  std::string FeatureModelDAO::selectionString(const std::string& simulationName) const {
    return FeatureModelsContract::COL_SIMULATIONNAME + " = '" + simulationName + "'";
  }

  std::vector<FeatureModel> FeatureModelDAO::toFeatureModels(const std::string& simulationName, Cursor& cursor) const {
    std::vector<FeatureModel> result;
    while (cursor.moveToNext()) {
      result.push_back(currentRowToFeatureModel(simulationName, cursor));
    }
    return result;
  }

  FeatureModel FeatureModelDAO::currentRowToFeatureModel(const std::string& simulationName, const Cursor& cursor) const {
    uint16_t permutation = cursor.getUShort(FeatureModelsContract::INDEX_PERMUTATION);
    std::string startPosition = cursor.getString(FeatureModelsContract::INDEX_STARTPOSITION);
    std::string endPosition = cursor.getString(FeatureModelsContract::INDEX_ENDPOSITION);
    std::string recordingName = cursor.getString(FeatureModelsContract::INDEX_RECORDINGNAME);
    uint32_t startFrame = cursor.getUInt(FeatureModelsContract::INDEX_STARTFRAME);
    uint32_t endFrame = cursor.getUInt(FeatureModelsContract::INDEX_ENDFRAME);
    Correlation correlation(startFrame, endFrame, Position::fromString(startPosition), Position::fromString(endPosition));
    FeatureSet featureSet = featureSetDao.load(recordingName, startFrame, endFrame);
    return FeatureModel(simulationName, correlation, permutation, std::move(featureSet));
  }

  void FeatureModelDAO::save(const FeatureModel& featureModel) const {
    Database::getInstance().insert(FeatureModelsContract::TABLENAME, toRow(featureModel));
    featureSetDao.save(featureModel.getFeatureSet());
  }

  std::vector<TableField> FeatureModelDAO::toRow(const FeatureModel& featureModel) const {
    std::vector<TableField> result;
    result.push_back({FeatureModelsContract::COL_SIMULATIONNAME, featureModel.getSimulationName()});
    result.push_back({FeatureModelsContract::COL_PERMUTATION, std::to_string(featureModel.getPermutation())});
    result.push_back({FeatureModelsContract::COL_STARTPOSITION, featureModel.getCorrelation().getStartPosition().toString()});
    result.push_back({FeatureModelsContract::COL_ENDPOSITION, featureModel.getCorrelation().getEndPosition().toString()});
    result.push_back({FeatureModelsContract::COL_RECORDINGNAME, featureModel.getFeatureSet().getRecordingName()});
    result.push_back({FeatureModelsContract::COL_STARTFRAME, std::to_string(featureModel.getCorrelation().getStartFrame())});
    result.push_back({FeatureModelsContract::COL_ENDFRAME, std::to_string(featureModel.getCorrelation().getEndFrame())});
    return result;
  }

} // namespace FeatureExtraction
