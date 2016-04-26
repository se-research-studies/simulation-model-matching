#include "featuremodeldao.h"

#include <FeatureSimulationCommon/MakeUnique>
#include <FeatureSimulationCommon/DataManagement/Database>

namespace Common {

  FeatureModelDAO::FeatureModelDAO() {
  }

  FeatureModelDAO::~FeatureModelDAO() {
  }

  std::vector<std::unique_ptr<FeatureModel>> FeatureModelDAO::load(const std::string& simulationName) {
    Database::getInstance().beginTransaction();
    Cursor cursor = Database::getInstance().query(FeatureModelsContract::TABLENAME, {"*"}, selectionString(simulationName));
    std::vector<std::unique_ptr<FeatureModel>> result = toFeatureModels(simulationName, cursor);
    Database::getInstance().endTransaction();
    return result;
  }

  std::string FeatureModelDAO::selectionString(const std::string& simulationName) const {
    return FeatureModelsContract::COL_SIMULATIONNAME + " = '" + simulationName + "'";
  }

  std::vector<std::unique_ptr<FeatureModel> > FeatureModelDAO::toFeatureModels(const std::string& simulationName, Cursor& cursor) const {
    std::vector<std::unique_ptr<FeatureModel>> result;
    while (cursor.moveToNext()) {
      result.push_back(currentRowToFeatureModel(simulationName, cursor));
    }
    return result;
  }

  std::unique_ptr<FeatureModel> FeatureModelDAO::currentRowToFeatureModel(const std::string& simulationName, const Cursor& cursor) const {
    uint16_t permutation = cursor.getUShort(FeatureModelsContract::INDEX_PERMUTATION);
    std::string startPosition = cursor.getString(FeatureModelsContract::INDEX_STARTPOSITION);
    std::string endPosition = cursor.getString(FeatureModelsContract::INDEX_ENDPOSITION);
    std::string recordingName = cursor.getString(FeatureModelsContract::INDEX_RECORDINGNAME);
    uint32_t startFrame = cursor.getUInt(FeatureModelsContract::INDEX_STARTFRAME);
    uint32_t endFrame = cursor.getUInt(FeatureModelsContract::INDEX_ENDFRAME);
    Correlation correlation(startFrame, endFrame, Position::fromString(startPosition), Position::fromString(endPosition));
    return std::make_unique<FeatureModel>(simulationName, correlation, permutation);
  }

  void FeatureModelDAO::save(const FeatureModel& featureModel) {
    Database::getInstance().beginTransaction();
    Database::getInstance().insert(FeatureModelsContract::TABLENAME, toRow(featureModel));
    Database::getInstance().endTransaction();
  }

  std::vector<TableField> FeatureModelDAO::toRow(const FeatureModel& featureModel) const {
    std::vector<TableField> result;
    result.push_back({FeatureModelsContract::COL_SIMULATIONNAME, featureModel.simulationName});
    result.push_back({FeatureModelsContract::COL_PERMUTATION, std::to_string(featureModel.permutation)});
    result.push_back({FeatureModelsContract::COL_STARTPOSITION, featureModel.correlation.startPosition.toString()});
    result.push_back({FeatureModelsContract::COL_ENDPOSITION, featureModel.correlation.endPosition.toString()});
    result.push_back({FeatureModelsContract::COL_RECORDINGNAME, featureModel.featureSet->getRecordingName()});
    result.push_back({FeatureModelsContract::COL_STARTFRAME, std::to_string(featureModel.correlation.startFrame)});
    result.push_back({FeatureModelsContract::COL_ENDFRAME, std::to_string(featureModel.correlation.endFrame)});
    return result;
  }

} // namespace FeatureExtraction
