#pragma once

#include <map>

namespace NoiseSimulation {

    template <typename SavableType>
    class DataSource
    {
    public:
        DataSource() {}
        virtual ~DataSource() {}

    public:
        virtual void save(SavableType& savable) const = 0;
        virtual SavableType load(const std::map<std::string, std::string>& keys) const = 0;
    };

} // namespace NoiseSimulation

