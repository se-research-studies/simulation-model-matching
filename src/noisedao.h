#pragma once

#include <NoiseSimulation/DataAccessObject>
#include <NoiseSimulation/Noise>

namespace NoiseSimulation {

    class NoiseDAO : public DataAccessObject<Noise>
    {
    public:
        NoiseDAO();
        virtual ~NoiseDAO();

    public:
        Noise load(const std::string& videoFilename) const;
    };

} // namespace NoiseSimulation

