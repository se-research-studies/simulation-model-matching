#pragma once

#include <map>
#include <memory>

#include <NoiseSimulation/DataSource>

namespace NoiseSimulation {

    template <typename SavableType>
    class DataAccessObject
    {
    public:
        DataAccessObject() {}
        virtual ~DataAccessObject() {}

    public:
        void save(SavableType& savable) const {
            dataSource->save(savable);
        }

    protected:
        SavableType load(const std::map<std::string, std::string>& keys) const {
            return dataSource->load(keys);
        }

    private:
        std::unique_ptr<DataSource<SavableType>> dataSource;
    };

} // namespace NoiseSimulation

