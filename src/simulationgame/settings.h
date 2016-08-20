#pragma once

#include <string>

namespace SimulationGame {

    struct Settings {
        std::string cid = "111";
        std::string freq = "10";
        std::string database = "./data.sqlite";
        std::string configurationFile;
        std::string autopilot;
        uint32_t frameLimit = 0;
        float featureScale = 0.25;
        int featureSize = 10;
        std::string correlationFile;
        bool showGui = false;
        uint32_t repetitions = 1;
    };

} // namespace SimulationGame

