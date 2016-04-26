#pragma once

#include <FeatureSimulationCommon/Data/FeatureModel>
#include <FeatureSimulationCommon/DataManagement/Cursor>
#include <FeatureSimulationCommon/DataManagement/TableField>

namespace Common {

  namespace FeatureModelsContract {
    std::string TABLENAME = "FeatureModels";
    std::string COL_SIMULATIONNAME = "simulationName";
    uint8_t INDEX_SIMULATIONNAME = 0;
    std::string COL_PERMUTATION = "permutation";
    uint8_t INDEX_PERMUTATION = 1;
    std::string COL_STARTPOSITION = "startPosition";
    uint8_t INDEX_STARTPOSITION = 2;
    std::string COL_ENDPOSITION = "endPosition";
    uint8_t INDEX_ENDPOSITION = 3;
    std::string COL_RECORDINGNAME = "recordingName";
    uint8_t INDEX_RECORDINGNAME = 4;
    std::string COL_STARTFRAME = "startFrame";
    uint8_t INDEX_STARTFRAME = 5;
    std::string COL_ENDFRAME = "endFrame";
    uint8_t INDEX_ENDFRAME = 6;
  }

  class FeatureModelDAO
  {
  public:
    FeatureModelDAO();
    virtual ~FeatureModelDAO();

  public:
    std::vector<std::unique_ptr<FeatureModel>> load(const std::string& simulationName);
    void save(const FeatureModel& featureModel);

  private:
    std::string selectionString(const std::string& simulationName) const;
    std::vector<std::unique_ptr<FeatureModel>> toFeatureModels(const std::string& simulationName, Cursor& cursor) const;
    std::unique_ptr<FeatureModel> currentRowToFeatureModel(const std::string& simulationName, const Cursor& cursor) const;
    std::vector<TableField> toRow(const FeatureModel& featureModel) const;
  };

} // namespace FeatureExtraction

