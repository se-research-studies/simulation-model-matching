#pragma once

#include <memory>
#include <vector>

#include <NoiseSimulation/Frame>

namespace NoiseSimulation {

    class Recording
    {
    public:
        Recording();
        virtual ~Recording();

    public:
        std::string getFilename() const;

    private:
        std::string filename;
    };

} // namespace NoiseSimulation

