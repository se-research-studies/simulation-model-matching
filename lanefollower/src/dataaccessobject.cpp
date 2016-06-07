#include "dataaccessobject.h"

#include "database.h"

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

