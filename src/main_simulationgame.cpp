#include <iostream>
#include <limits>

#include "simulationgame/odvcontrol.h"
#include "simulationgame/participants/lanefollower.h"
#include <FeatureSimulation/SimulationGame/participantregistry.h>


// cid und freq als Argument mit defaults

int main(int argc, char *argv[]) {
    SimulationGame::OdvControl control;

    std::cout << "Press ENTER to start... " << std::endl;
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

    control.start();

    std::cout << "Press ENTER to stop... " << std::endl;
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

    SimulationGame::LaneFollower lf(argc, argv);
    int exitCode = lf.runModule();

    control.stop();

//    SimulationGame::ParticipantRegistry registry("111", "10");
//    registry.registerParticipant<SimulationGame::LaneFollower>("LaneFollower");

//    SimulationGame::AbstractParticipant&& laneFollower = std::move(registry.getParticipant("LaneFollower"));

    exit(EXIT_SUCCESS);
}
