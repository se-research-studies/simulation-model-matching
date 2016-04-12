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

    private:
        std::string filename;
        std::vector<std::unique_ptr<Frame>> frames;
    };

} // namespace NoiseSimulation

