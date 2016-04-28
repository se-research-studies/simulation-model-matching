#pragma once

#include <FeatureSimulation/Common/Data/FeatureModel>
#include <FeatureSimulation/Common/DataManagement/Cursor>
#include <FeatureSimulation/Common/DataManagement/FeatureSetDAO>
#include <FeatureSimulation/Common/DataManagement/TableField>

namespace Common {

  namespace FeatureModelsContract {
    static const std::string TABLENAME = "FeatureModels";
    static const std::string COL_SIMULATIONNAME = "simulationName";
    static const std::string COL_PERMUTATION = "permutation";
    static const std::string COL_STARTPOSITION = "startPosition";
    static const std::string COL_ENDPOSITION = "endPosition";
    static const std::string COL_RECORDINGNAME = "recordingName";
    static const std::string COL_STARTFRAME = "startFrame";
    static const std::string COL_ENDFRAME = "endFrame";
    static const uint8_t INDEX_SIMULATIONNAME = 0;
    static const uint8_t INDEX_PERMUTATION = 1;
    static const uint8_t INDEX_STARTPOSITION = 2;
    static const uint8_t INDEX_ENDPOSITION = 3;
    static const uint8_t INDEX_RECORDINGNAME = 4;
    static const uint8_t INDEX_STARTFRAME = 5;
    static const uint8_t INDEX_ENDFRAME = 6;
  }

  class FeatureModelDAO
  {
  public:
    FeatureModelDAO();
    virtual ~FeatureModelDAO();

  public:
    std::vector<FeatureModel> load(const std::string& simulationName) const;
    void save(const FeatureModel& featureModel) const;

  private:
    std::string selectionString(const std::string& simulationName) const;
    std::vector<FeatureModel> toFeatureModels(const std::string& simulationName, Cursor& cursor) const;
    FeatureModel currentRowToFeatureModel(const std::string& simulationName, const Cursor& cursor) const;
    std::vector<TableField> toRow(const FeatureModel& featureModel) const;

  private:
    FeatureSetDAO featureSetDao;
  };

} // namespace FeatureExtraction

