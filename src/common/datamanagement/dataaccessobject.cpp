#include "dataaccessobject.h"

#include <FeatureSimulation/Common/DataManagement/Database>

namespace Common {

  DataAccessObject::DataAccessObject() {
  }

  DataAccessObject::~DataAccessObject() {
  }

  void DataAccessObject::beginTransaction() const {
    Database::getInstance().beginTransaction();
  }

  void DataAccessObject::endTransaction() const {
    Database::getInstance().endTransaction();
  }

} // namespace Common
