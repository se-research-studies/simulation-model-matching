#include <iostream>
#include <limits>

#include "simulationgame/odvcontrol.h"
#include "simulationgame/participants/lanefollower.h"
#include <FeatureSimulation/SimulationGame/participantregistry.h>


// cid und freq als Argument mit defaults

int main(int argc, char *argv[]) {

    // Hardcoded settings for tests
    std::string cid = "111";
    std::string freq = "10";
    std::string configurationFile = "/home/sebastian/Uni/Bachelorarbeit/Code/resources/configuration";
    std::string participant = "LaneFollower";
    uint32_t frameLimit = 100;

    SimulationGame::OdvControl control(cid, freq, configurationFile);

    std::cout << "Press ENTER to start... " << std::endl;
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

    control.start();

    SimulationGame::ParticipantRegistry registry(cid, freq, frameLimit);
    registry.registerParticipant<SimulationGame::LaneFollower>(participant);

    std::unique_ptr<SimulationGame::AbstractParticipant> laneFollower = registry.getParticipant("LaneFollower");
    int exitCode = laneFollower->runModule();

    control.stop();

    exit(exitCode);
}
