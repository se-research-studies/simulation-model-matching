#pragma once

#include <FeatureSimulation/SimulationGame/odvcontrol.h>

namespace SimulationGame {

    class ParticipantRegistry;
    struct Settings;

    class GameRunner {
    public:
        GameRunner(SimulationGame::ParticipantRegistry& registry);
        virtual ~GameRunner();

    public:
        int start(const Settings& settings);
        
    private:
        static void waitForEnter();
        void prepareSimulation(const Settings& settings);
        int runSimulation(const Settings& settings);
        void finishSimulation();

    private:
        SimulationGame::ParticipantRegistry& registry;
        OdvControl control;
    };

} // namespace SimulationGame

