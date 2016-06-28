#include <iostream>

#include <FeatureSimulation/SimulationGame/gamerunner.h>
#include <FeatureSimulation/SimulationGame/participantregistry.h>
#include <FeatureSimulation/SimulationGame/settings.h>

#include <FeatureSimulation/SimulationGame/Participants/lanefollower.h>

int main(int argc, char *argv[]) {

    SimulationGame::Settings settings;

    SimulationGame::ParticipantRegistry registry(settings.cid, settings.freq);
    registry.registerParticipant<SimulationGame::LaneFollower>("LaneFollower");
    // Ausgeben welche Participants es gibt

    try {
        SimulationGame::GameRunner gameRunner(registry);
        gameRunner.start(settings);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    exit(EXIT_SUCCESS);
}
