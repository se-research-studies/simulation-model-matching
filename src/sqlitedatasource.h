#pragma once

#include <NoiseSimulation/DataSource>

namespace NoiseSimulation {

    template <typename SavableType>
    class SQLiteDataSource : public DataSource<SavableType>
    {
    public:
        SQLiteDataSource() {}
        virtual ~SQLiteDataSource() {}
    };

} // namespace NoiseSimulation

