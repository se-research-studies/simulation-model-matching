#include <unistd.h>

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -v VIDEOFILE -s SIMULATIONFILE" << std::endl;
        exit(EXIT_FAILURE);
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
            break;
        }
    }

    std::clog << "Using video " << videoFilename << " and sim " << simulationFilename << std::endl;

    //NoiseSimulation::SQLiteDataSource::createInstance();

    exit(EXIT_SUCCESS);
}
