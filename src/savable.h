#pragma once

#include <map>

namespace NoiseSimulation {

    class Savable
    {
    protected:
        Savable();
        virtual ~Savable();

    public:
        virtual std::map<std::string, std::string> toMap() const = 0;
    };

} // namespace NoiseSimulation

