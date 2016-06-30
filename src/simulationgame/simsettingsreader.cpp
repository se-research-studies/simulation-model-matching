#include "simsettingsreader.h"

#include <stdexcept>

static const struct option simulationGameLongopts[] = {
    // Operation arguments
    {"cid", optional_argument, nullptr, SimulationGame::SimSettingsReader::CID},
    {"freq", optional_argument, nullptr, SimulationGame::SimSettingsReader::FREQ},
    {"conf", optional_argument, nullptr, SimulationGame::SimSettingsReader::CONFIG_FILE},
    {"participant", required_argument, nullptr, SimulationGame::SimSettingsReader::PARTICIPANT},
    {"frames", optional_argument, nullptr, SimulationGame::SimSettingsReader::FRAME_LIMIT},
    {"scale", optional_argument, nullptr, SimulationGame::SimSettingsReader::FEATURE_SCALE},
    {"size", optional_argument, nullptr, SimulationGame::SimSettingsReader::FEATURE_SIZE},
    {"cor", required_argument, nullptr, SimulationGame::SimSettingsReader::CORRELATION_FILE},
    {"guiEnabled", optional_argument, nullptr, SimulationGame::SimSettingsReader::SHOW_GUI},
    {"repetitions", optional_argument, nullptr, SimulationGame::SimSettingsReader::REPETITIONS},
    {0, 0, 0, 0} //Required by getopt_long_only to mark the end of the arrays
};

namespace SimulationGame {

    void SimSettingsReader::printUsage(char* programName)
    {
        fprintf(stderr, "Usage: %s -participant='name' [-options]\n", programName);
        fprintf(stderr,
                "  -cid               Optional. cid for OpenDaVinci. Default is 111.\n"
                "  -freq              Optional. freq for OpenDaVinci. Default is 10.\n"
                "  -conf              Optional. Path to OpenDaVinci conf file.\n"
                "  -participant       Required. Name of Algorithm to use.\n"
                "  -frames            Optional. Maximum number of frames. Default is 0, ie. no limit.\n"
                "  -scale             Optional. Scale factor for feature size. Default is 0.25.\n"
                "  -size              Optional. Absolute size for features. Default is 10. Supersedes scale if set.\n"
                "  -cor               Required. Path to .cor file.\n"
                "  -guiEnabled        Optional. Default is false\n"
                "  -repetitions       Optional. Number of repetitions of all permutations. Default is 1.\n"
                "\n"
                "  Available participants:\n"
                "    - LaneFollower\n"
                );
    }

    Settings SimSettingsReader::readSettings(int argc, char* argv[])
    {
        Settings settings;
        int optIndex = 0;
        while ((optIndex = getopt_long_only(argc, argv, "", simulationGameLongopts, nullptr)) != -1) {
            switch (optIndex) {
            case CID:
                settings.cid = std::string(optarg);
                break;
            case FREQ:
                settings.freq = std::string(optarg);
                break;
            case CONFIG_FILE:
                settings.configurationFile =  std::string(optarg);
                break;
            case PARTICIPANT:
                settings.participant =  std::string(optarg);
                break;
            case FRAME_LIMIT:
                settings.frameLimit = atoi(optarg);
                break;
            case FEATURE_SCALE:
                settings.featureScale = atof(optarg);
                break;
            case FEATURE_SIZE:
                settings.featureSize = atof(optarg);
                break;
            case CORRELATION_FILE:
                settings.correlationFile =  std::string(optarg);
                break;
            case SHOW_GUI:
                settings.showGui = atoi(optarg);
                break;
            case REPETITIONS:
                settings.repetitions = atoi(optarg);
                break;            
            default:
                printUsage(argv[0]);
                throw std::runtime_error("Invalid argument");
            }
        }
        return settings;
    }

} // namespace FeatureSetCreation
