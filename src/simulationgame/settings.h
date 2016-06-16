#pragma once

#include <string>

namespace SimulationGame {

    struct Settings {
        std::string cid = "111";
        std::string freq = "10";
        std::string configurationFile = "/home/sebastian/Uni/Bachelorarbeit/Code/resources/configuration";
        std::string participant = "LaneFollower";
        uint32_t frameLimit = 300;
        //int featureScale;
        //int featureSize;
        std::string featureSource = "../resources/straightroad.rec";

    };

} // namespace SimulationGame

