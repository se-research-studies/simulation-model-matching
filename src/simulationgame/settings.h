#pragma once

#include <string>

namespace SimulationGame {

    struct Settings {
        std::string cid = "111";
        std::string freq = "10";
        std::string configurationFile = "/home/sebastian/Uni/Bachelorarbeit/Code/resources/configuration";
        std::string participant = "LaneFollower";
        uint32_t frameLimit = 100;
        float featureScale = 0.25;
        int featureSize = 10;
        std::string correlationFile = "../resources/SEM_Test_Track-overtaking.cor";
        bool showGui = false;
    };

} // namespace SimulationGame

