#include <iostream>
#include <limits>

#include "simulationgame/odvcontrol.h"

int main(int argc, char *argv[]) {

    SimulationGame::OdvControl control;

    std::cout << "Press ENTER to start... " << std::endl;
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

    control.start();

    std::cout << "Press ENTER to stop... " << std::endl;
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );

    control.stop();

    exit(EXIT_SUCCESS);
}
