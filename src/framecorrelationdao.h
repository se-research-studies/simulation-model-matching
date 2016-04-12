#pragma once

#include <NoiseSimulation/DataAccessObject>
#include <NoiseSimulation/FrameCorrelation>

namespace NoiseSimulation {

    class FrameCorrelationDAO : public DataAccessObject<FrameCorrelation>
    {
    public:
        FrameCorrelationDAO();
        virtual ~FrameCorrelationDAO();

    public:
        FrameCorrelation load(const std::string& videoFilename, const std::string& simFilename) const;
    };

}
