#pragma once

#include <vector>

#include <FeatureSimulation/Common/DataManagement/dataaccessobject.h>
#include <FeatureSimulation/Common/DataManagement/tablefield.h>
#include <FeatureSimulation/Common/Data/simulationdata.h>

namespace Common {

    namespace SimulationDataContract {
        static const std::string TABLENAME = "SimulationData";
        static const std::string COL_SIMULATIONNAME = "simulationName";
        static const std::string COL_CORRELATIONFILE = "correlationFile";
        static const std::string COL_PERMUTATIONINDEX = "permutationIndex";
        static const std::string COL_FRAMES = "frames";
        static const std::string COL_COMPUTATIONTIMES = "computationTimes";
        static const std::string COL_AVERAGECOMPUTATIONTIME = "averageComputationTime";
        static const std::string COL_MINCOMPUTATIONTIME = "minComputationTime";
        static const std::string COL_MAXCOMPUTATIONTIME = "maxComputationTime";
        static const std::string COL_TOTALCOMPUTATIONTIME = "totalComputationTime";
        static const std::string COL_LEFTSTEERINGS = "leftSteerings";
        static const std::string COL_RIGHTSTEERINGS = "rightSteerings";
        static const std::string COL_ACCELERATIONS = "accelerations";
        static const std::string COL_DECELERATIONS = "decelerations";
        static const std::string COL_MEMORY = "memory";
        static const std::string COL_AVERAGEMEMORY = "averageMemory";
        static const std::string COL_MINMEMORY = "minMemory";
        static const std::string COL_MAXMEMORY = "maxMemory";
        static const std::string COL_DATE = "date";
    }

    class SimulationDataDAO : public DataAccessObject {
    public:
        void ensureTable() const;
        void save(const SimulationData& data) const;
        std::vector<TableField> toRow(const SimulationData& data) const;

    private:
        std::string currentDateTime() const;
    };

} // namespace Common

