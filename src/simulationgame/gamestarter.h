#pragma once

#include <string>

namespace SimulationGame {

    class GameStarter {
    public:
        GameStarter(const std::string& simulationFile, const std::string& recordingFile);
        virtual ~GameStarter();

    public:
        void start();
    };

} // namespace SimulationGame

