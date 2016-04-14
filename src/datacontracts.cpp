#include "datacontracts.h"

namespace NoiseSimulation {

    namespace NoiseFields {

        std::string videoFilename()
        {
            return "videoFilename";
        }

        std::string frameIndex()
        {
            return "frameIndex";
        }

        std::string x()
        {
            return "x";
        }

        std::string y()
        {
            return "y";
        }

        std::string radius()
        {
            return "radius";
        }
    }

    namespace FrameCorrelationFields {

        std::string videoFilename()
        {
            return "videoFilename";
        }

        std::string simulationFilename()
        {
            return "simulationFilename";
        }

        std::string videoStart()
        {
            return "videoStart";
        }

        std::string videoEnd()
        {
            return "videoEnd";
        }

        std::string simulationStart()
        {
            return "simulationStart";
        }

        std::string simulationEnd()
        {
            return "simulationEnd";
        }

    }

    namespace IgnoredAreaFields {

        std::string videoFilename()
        {
            return "videoFilename";
        }

        std::string topLeftX()
        {
            return "topLeftX";
        }

        std::string topLeftY()
        {
            return "topLeftY";
        }

        std::string bottomLeftX()
        {
            return "bottomLeftX";
        }

        std::string bottomLeftY()
        {
            return "bottomLeftY";
        }

        std::string topRightX()
        {
            return "topRightX";
        }

        std::string topRightY()
        {
            return "topRightY";
        }

        std::string bottomRightX()
        {
            return "bottomRightX";
        }

        std::string bottomRightY()
        {
            return "bottomRightY";
        }
    }

} // namespace NoiseSimulation
