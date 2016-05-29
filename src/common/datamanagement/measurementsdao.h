#pragma once

#include <vector>

#include <FeatureSimulation/Common/DataManagement/DataAccessObject>
#include <FeatureSimulation/Common/DataManagement/TableField>

#include <FeatureSimulation/Common/Data/Measurements>

namespace Common {

    namespace MeasurementsContract {
        static const std::string TABLENAME = "Measurements";
        static const std::string COL_SIMULATIONNAME = "simulationName";
        static const std::string COL_RECORDINGNAME = "recordingName";
        static const std::string COL_STEPS = "steps";
        static const std::string COL_COMPUTATIONTIME = "computationTime";
        static const std::string COL_LAPTIME = "lapTime";
        static const std::string COL_STEERINGACTIONS = "steeringActions";
        static const std::string COL_MEMORY = "memory";
        static const uint8_t INDEX_SIMULATIONNAME = 0;
        static const uint8_t INDEX_RECORDINGNAME = 1;
        static const uint8_t INDEX_STEPS = 2;
        static const uint8_t INDEX_COMPUTATIONTIME = 3;
        static const uint8_t INDEX_LAPTIME = 4;
        static const uint8_t INDEX_STEERINGACTIONS = 5;
        static const uint8_t INDEX_MEMORY = 6;
    }

    class MeasurementsDAO : public DataAccessObject {
    public:
        void ensureTable() const;
        void save(const Measurements& measurements) const;
        std::vector<TableField> toRow(const Measurements& measurements) const;
    };

} // namespace Common

