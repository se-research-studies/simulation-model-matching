#include "measurementsdao.h"

#include "database.h"
#include "tablecolumn.h"

void MeasurementsDAO::ensureTable() const {
    std::vector<TableColumn> columns;
    columns.push_back({MeasurementsContract::COL_SIMULATIONNAME, "TEXT"});
    columns.push_back({MeasurementsContract::COL_RECORDINGNAME, "TEXT"});
    columns.push_back({MeasurementsContract::COL_STEPS, "INTEGER"});
    columns.push_back({MeasurementsContract::COL_COMPUTATIONTIME, "INTEGER"});
    columns.push_back({MeasurementsContract::COL_LAPTIME, "INTEGER"});
    columns.push_back({MeasurementsContract::COL_STEERINGACTIONS, "INTEGER"});
    columns.push_back({MeasurementsContract::COL_MEMORY, "INTEGER"});
    Database::getInstance().createTable(MeasurementsContract::TABLENAME, columns);
}

void MeasurementsDAO::save(const Measurements& measurements) const {
    Database::getInstance().insert(MeasurementsContract::TABLENAME, toRow(measurements));
}

std::vector<TableField> MeasurementsDAO::toRow(const Measurements& measurements) const {
    std::vector<TableField> result;
    result.push_back({MeasurementsContract::COL_SIMULATIONNAME, measurements.getSimulationName()});
    result.push_back({MeasurementsContract::COL_RECORDINGNAME, measurements.getRecordingName()});
    result.push_back({MeasurementsContract::COL_STEPS, std::to_string(measurements.getSteps())});
    result.push_back({MeasurementsContract::COL_COMPUTATIONTIME, std::to_string(measurements.getComputationTime())});
    result.push_back({MeasurementsContract::COL_LAPTIME, std::to_string(measurements.getLapTime())});
    result.push_back({MeasurementsContract::COL_STEERINGACTIONS, std::to_string(measurements.getSteeringActions())});
    result.push_back({MeasurementsContract::COL_MEMORY, std::to_string(measurements.getMemory())});
    return result;
}
