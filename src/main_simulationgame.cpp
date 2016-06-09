#include <iostream>
#include <limits>

#include "simulationgame/odvcontrol.h"
#include "simulationgame/participants/lanefollower.h"
#include <FeatureSimulation/SimulationGame/participantregistry.h>

int main(int argc, char *argv[]) {

    // Ausgeben welche Participants es gibt
    // Hardcoded settings for tests
    std::string cid = "111";
    std::string freq = "10";
    std::string configurationFile = "/home/sebastian/Uni/Bachelorarbeit/Code/resources/configuration";
    std::string participant = "LaneFollower";
    uint32_t frameLimit = 300;
    //int featureScale;
    //int featureSize;
    std::string featureSource = "../resources/straightroad.rec";

    SimulationGame::OdvControl control(cid, freq, configurationFile);

//    std::cout << "Press ENTER to start... " << std::endl;
//    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

    control.start();

    SimulationGame::ParticipantRegistry registry(cid, freq);
    registry.registerParticipant<SimulationGame::LaneFollower>("LaneFollower");

    std::unique_ptr<SimulationGame::AbstractParticipant> laneFollower = registry.getParticipant(participant);
    int exitCode = laneFollower->runModule(frameLimit, featureSource);

    control.stop();

    exit(exitCode);
}
