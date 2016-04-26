#include "featuremodeldao.h"

#include <FeatureSimulationCommon/MakeUnique>
#include <FeatureSimulationCommon/DataManagement/Database>

namespace Common {

  FeatureModelDAO::FeatureModelDAO()
  {
  }

  FeatureModelDAO::~FeatureModelDAO()
  {
  }

  std::vector<std::unique_ptr<FeatureModel>> FeatureModelDAO::load(const std::string& simulationFilename)
  {
    Database::getInstance().beginTransaction();
    std::vector<std::unique_ptr<FeatureModel>> result;
    Cursor cursor = Database::getInstance().query(FeatureModelsContract::TABLENAME, {"*"}, selectionString(simulationFilename));
    while (cursor.moveToNext()) {
      std::string simulationName = cursor.getString(FeatureModelsContract::INDEX_SIMULATIONNAME);
      uint16_t permutation = cursor.getUShort(FeatureModelsContract::INDEX_PERMUTATION);
      std::string startPosition = cursor.getString(FeatureModelsContract::INDEX_STARTPOSITION);
      std::string endPosition = cursor.getString(FeatureModelsContract::INDEX_ENDPOSITION);
      std::string recordingName = cursor.getString(FeatureModelsContract::INDEX_RECORDINGNAME);
      uint32_t startFrame = cursor.getUInt(FeatureModelsContract::INDEX_STARTFRAME);
      uint32_t endFrame = cursor.getUInt(FeatureModelsContract::INDEX_ENDFRAME);
      Correlation correlation(startFrame, endFrame, Position::fromString(startPosition), Position::fromString(endPosition));
      std::unique_ptr<FeatureModel> featureModel = std::make_unique<FeatureModel>(simulationName, correlation, permutation);
      result.push_back(move(featureModel));
    }
    Database::getInstance().endTransaction();
    return result;
  }

  void FeatureModelDAO::save(FeatureModel& featureModel)
  {
    Database::getInstance().beginTransaction();
    std::vector<TableField> row;
    row.push_back({FeatureModelsContract::COL_SIMULATIONNAME, featureModel.simulationName});
    row.push_back({FeatureModelsContract::COL_PERMUTATION, std::to_string(featureModel.permutation)});
    row.push_back({FeatureModelsContract::COL_STARTPOSITION, featureModel.correlation.startPosition.toString()});
    row.push_back({FeatureModelsContract::COL_ENDPOSITION, featureModel.correlation.endPosition.toString()});
    row.push_back({FeatureModelsContract::COL_RECORDINGNAME, featureModel.featureSet->getRecordingName()});
    row.push_back({FeatureModelsContract::COL_STARTFRAME, std::to_string(featureModel.correlation.startFrame)});
    row.push_back({FeatureModelsContract::COL_ENDFRAME, std::to_string(featureModel.correlation.endFrame)});
    Database::getInstance().insert(FeatureModelsContract::TABLENAME, row);
    Database::getInstance().endTransaction();
  }

  std::string FeatureModelDAO::selectionString(const std::string& simulationFilename) const
  {
    return FeatureModelsContract::COL_SIMULATIONNAME + " = '" + simulationFilename + "'";
  }

} // namespace FeatureExtraction
