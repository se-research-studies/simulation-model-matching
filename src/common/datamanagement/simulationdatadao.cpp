#include "simulationdatadao.h"

#include <ctime>
#include <iomanip>

#include <FeatureSimulation/Common/DataManagement/database.h>

namespace Common {

    void SimulationDataDAO::ensureTable() const {
        std::vector<TableColumn> columns;
        columns.push_back({SimulationDataContract::COL_SIMULATIONNAME, "TEXT"});
        columns.push_back({SimulationDataContract::COL_CORRELATIONFILE, "TEXT"});
        columns.push_back({SimulationDataContract::COL_FRAMES, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_COMPUTATIONTIMES, "TEXT"});
        columns.push_back({SimulationDataContract::COL_AVERAGECOMPUTATIONTIME, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_MINCOMPUTATIONTIME, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_MAXCOMPUTATIONTIME, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_TOTALCOMPUTATIONTIME, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_LEFTSTEERINGS, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_RIGHTSTEERINGS, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_ACCELERATIONS, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_DECELERATIONS, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_MEMORY, "TEXT"});
        columns.push_back({SimulationDataContract::COL_AVERAGEMEMORY, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_MINMEMORY, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_MAXMEMORY, "INTEGER"});
        columns.push_back({SimulationDataContract::COL_DATE, "TEXT"});
        Database::getInstance().createTable(SimulationDataContract::TABLENAME, columns);
    }

    void SimulationDataDAO::save(const SimulationData& data) const {
        Database::getInstance().insert(SimulationDataContract::TABLENAME, toRow(data));
    }

    std::vector<TableField> SimulationDataDAO::toRow(const SimulationData& data) const {
        std::vector<TableField> result;
        result.push_back({SimulationDataContract::COL_SIMULATIONNAME, data.getSimulationName()});
        result.push_back({SimulationDataContract::COL_CORRELATIONFILE, data.getCorrelationFile()});
        result.push_back({SimulationDataContract::COL_FRAMES, std::to_string(data.getFrames())});
        result.push_back({SimulationDataContract::COL_COMPUTATIONTIMES, data.computationTimesToString()});
        result.push_back({SimulationDataContract::COL_AVERAGECOMPUTATIONTIME, std::to_string(data.getAverageComputationTime())});
        result.push_back({SimulationDataContract::COL_MINCOMPUTATIONTIME, std::to_string(data.getMinComputationTime())});
        result.push_back({SimulationDataContract::COL_MAXCOMPUTATIONTIME, std::to_string(data.getMaxComputationTime())});
        result.push_back({SimulationDataContract::COL_TOTALCOMPUTATIONTIME, std::to_string(data.getTotalComputationTime())});
        result.push_back({SimulationDataContract::COL_LEFTSTEERINGS, std::to_string(data.getLeftSteerings())});
        result.push_back({SimulationDataContract::COL_RIGHTSTEERINGS, std::to_string(data.getRightSteerings())});
        result.push_back({SimulationDataContract::COL_ACCELERATIONS, std::to_string(data.getAccelerations())});
        result.push_back({SimulationDataContract::COL_DECELERATIONS, std::to_string(data.getDecelerations())});
        result.push_back({SimulationDataContract::COL_MEMORY, data.memoryToString()});
        result.push_back({SimulationDataContract::COL_AVERAGEMEMORY, std::to_string(data.getAverageMemory())});
        result.push_back({SimulationDataContract::COL_MINMEMORY, std::to_string(data.getMinMemory())});
        result.push_back({SimulationDataContract::COL_MAXMEMORY, std::to_string(data.getMaxMemory())});
        result.push_back({SimulationDataContract::COL_DATE, currentDateTime()});
        return result;
    }

    std::string SimulationDataDAO::currentDateTime() const
    {
        time_t rawtime = std::time(nullptr);
        std::tm* timeinfo = std::localtime(&rawtime);
        char buffer[80];
        strftime(buffer, 80, "%F %T", timeinfo);
        return std::string(buffer);
    }

} // namespace Common
