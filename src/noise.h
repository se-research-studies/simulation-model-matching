#pragma once

#include <NoiseSimulation/Loadable>
#include <NoiseSimulation/Point>
#include <NoiseSimulation/Savable>

namespace NoiseSimulation {

    class Frame;

    class Noise : public Savable, public Loadable
    {
    public:
        Noise();
        virtual ~Noise();

    public:
        std::map<std::string, std::string> toMap() const override;

    private:
        void setDataFromMap(const std::map<std::string, std::string>& map) override;

    private:
        Frame* frame;
        Point coordinates;
        uint16_t radius = 0;
    };

}

