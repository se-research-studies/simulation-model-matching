#include <iostream>

#include <getopt.h>

#include <SimulationGame/GameStarter>

static const struct option longopts[] = {
    // Operation arguments
    {"sim", required_argument, nullptr, 0},
    {"rec", required_argument, nullptr, 1},
    {0, 0, 0, 0} //Required by getopt_long_only to mark the end of the arrays
};

void printUsage(char* programName) {
    fprintf(stderr, "Usage: %s -sim='SIMULATIONFILE' -rec='RECORDINGFILE'\n", programName);
}

int main(int argc, char *argv[]) {
//    if (argc == 1) {
//        printUsage(argv[0]);
//        exit(EXIT_FAILURE);
//    }

    int optIndex = 0;

    std::string simFile;
    std::string recFile;

    while ((optIndex = getopt_long_only(argc, argv, "", longopts, nullptr)) != -1) {
        switch (optIndex) {
        case 0:
            simFile = std::string(optarg);
            break;
        case 1:
            recFile = std::string(optarg);
            break;
        default:
            printUsage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    SimulationGame::GameStarter starter(simFile, recFile);
    starter.start();

    exit(EXIT_SUCCESS);
}
