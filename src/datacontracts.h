#pragma once

#include <string>

namespace NoiseSimulation {

    namespace NoiseFields {
        extern std::string videoFilename();
        extern std::string frameIndex();
        extern std::string x();
        extern std::string y();
        extern std::string radius();
    }

    namespace FrameCorrelationFields {
        extern std::string videoFilename();
        extern std::string simulationFilename();
        extern std::string videoStart();
        extern std::string videoEnd();
        extern std::string simulationStart();
        extern std::string simulationEnd();
    }

    namespace IgnoredAreaFields {
        extern std::string videoFilename();
        extern std::string topLeftX();
        extern std::string topLeftY();
        extern std::string bottomLeftX();
        extern std::string bottomLeftY();
        extern std::string topRightX();
        extern std::string topRightY();
        extern std::string bottomRightX();
        extern std::string bottomRightY();
    }
}
