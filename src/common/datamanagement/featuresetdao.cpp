#include "featuresetdao.h"

#include <FeatureSimulationCommon/DataManagement/Database>

namespace Common {

  FeatureSetDAO::FeatureSetDAO()
  {
  }

  FeatureSetDAO::~FeatureSetDAO()
  {
  }

  std::unique_ptr<FeatureSet> FeatureSetDAO::load(const std::string recordingFilename) {
    std::unique_ptr<FeatureSet> result;
    Database::getInstance().beginTransaction();
    std::string selection = FeatureSetsContract::COL_RECORDINGFILENAME + " = '" + recordingFilename + "'";
    Cursor cursor = Database::getInstance().query(FeatureSetsContract::TABLENAME, {"*"}, selection);
    while (cursor.moveToNext()) {

    }
    Database::getInstance().endTransaction();
    return result;
  }

  void FeatureSetDAO::save(FeatureSet& featureSet) {
    Database::getInstance().beginTransaction();
    std::vector<std::pair<std::string, std::string>> content;
    Database::getInstance().insert(FeatureSetsContract::TABLENAME, content);
    Database::getInstance().endTransaction();
  }

} // namespace FeatureExtraction
