#pragma once

#include <NoiseSimulation/DataSource>

namespace NoiseSimulation {

    template <typename SavableType>
    class FileDataSource : public DataSource<SavableType>
    {
    public:
        FileDataSource() {}
        virtual ~FileDataSource() {}
    };

} // namespace NoiseSimulation

