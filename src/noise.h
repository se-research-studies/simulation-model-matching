#pragma once

#include <NoiseSimulation/Savable>

namespace NoiseSimulation {

    class Noise : public Savable
    {
    public:
        Noise();
        virtual ~Noise();

    public:
        std::map<std::string, std::string> toMap() const override;
    };

}

