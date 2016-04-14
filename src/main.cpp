#include <unistd.h>

#include <iostream>

#include <NoiseSimulation/SQLiteDataSource>

int main(int argc, char* argv[])
{
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -v VIDEOFILE -s SIMULATIONFILE" << std::endl;
    }

    std::string videoFilename;
    std::string simulationFilename;

    int opt;
    while ((opt = getopt(argc, argv, "v:s:")) != -1) {
        switch (opt) {
        case 'v':
            videoFilename = optarg;
            break;
        case 's':
            simulationFilename = optarg;
            break;
        default:
            exit(EXIT_FAILURE);
            break;
        }
    }

    std::clog << "Using video " << videoFilename << " and sim " << simulationFilename << std::endl;

    NoiseSimulation::SQLiteDataSource::createInstance();

    exit(EXIT_SUCCESS);
}
