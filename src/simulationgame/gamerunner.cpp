#include "gamerunner.h"

#include <future>
#include <iostream>

#include <FeatureSimulation/SimulationGame/abstractparticipant.h>
#include <FeatureSimulation/SimulationGame/participantregistry.h>
#include <FeatureSimulation/SimulationGame/settings.h>

namespace SimulationGame {

    GameRunner::GameRunner(SimulationGame::ParticipantRegistry& registry)
        : registry(registry) {
    }

    GameRunner::~GameRunner() {
    }

    int GameRunner::start(const Settings& settings)
    {
        std::cout << "Press ENTER to start and again enter to stop before frame limit is reached... " << std::endl;
        waitForEnter();

        prepareSimulation(settings);
        int result = runSimulation(settings);
        finishSimulation();
        return result;
    }

    void GameRunner::waitForEnter()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter pressed..." << std::endl;
    }

    void GameRunner::prepareSimulation(const Settings& settings)
    {
        control.start(settings.cid, settings.freq, settings.configurationFile);
    }

    int GameRunner::runSimulation(const Settings& settings)
    {
        std::unique_ptr<AbstractParticipant> participant = registry.getParticipant(settings.participant);
        std::future<odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode> simulation = std::async(std::launch::async, &AbstractParticipant::runModule, participant.get(), settings.frameLimit, settings.featureSource);
        std::future<void> enterKey = std::async(std::launch::async, &GameRunner::waitForEnter);
        while (simulation.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
            if (enterKey.wait_for(std::chrono::milliseconds(10)) == std::future_status::ready) {
                participant->forceQuit();
            }
        }
        std::cout << "Done" << std::endl;
        return simulation.get();
    }

    void GameRunner::finishSimulation()
    {
        control.stop();
    }


} // namespace SimulationGame
