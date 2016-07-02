#include "simsettingsreader.h"

#include <stdexcept>

static const struct option simulationGameLongopts[] = {
    // Operation arguments
    {"cid", optional_argument, nullptr, SimulationGame::SimSettingsReader::CID},
    {"freq", optional_argument, nullptr, SimulationGame::SimSettingsReader::FREQ},
    {"db", optional_argument, nullptr, SimulationGame::SimSettingsReader::DATABASE},
    {"conf", optional_argument, nullptr, SimulationGame::SimSettingsReader::CONFIG_FILE},
    {"participant", required_argument, nullptr, SimulationGame::SimSettingsReader::PARTICIPANT},
    {"frames", optional_argument, nullptr, SimulationGame::SimSettingsReader::FRAME_LIMIT},
    {"scale", optional_argument, nullptr, SimulationGame::SimSettingsReader::FEATURE_SCALE},
    {"size", optional_argument, nullptr, SimulationGame::SimSettingsReader::FEATURE_SIZE},
    {"cor", optional_argument, nullptr, SimulationGame::SimSettingsReader::CORRELATION_FILE},
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
                "  -db                Optional. Database file. Default is ./data.sqlite.\n"
                "  -conf              Optional. Path to OpenDaVinci conf file. File must be in same folder as executable if not set.\n"
                "  -participant       Required. Name of Algorithm to use.\n"
                "  -frames            Optional. Integer. Maximum number of frames. Default is 0, ie. no limit. If set to 0 simulation can be stopped by pressing enter.\n"
                "  -scale             Optional. Float. Scale factor for feature size. Default is 0.25.\n"
                "  -size              Optional. Integer. Absolute size for features. Default is 10. Supersedes scale if not 0.\n"
                "  -cor               Optional. Path to .cor file. If not set no features will be used.\n"
                "  -guiEnabled        Optional. Boolean. Default is 0\n"
                "  -repetitions       Optional. Integer. Number of repetitions of all permutations. Default is 1.\n"
                "\n"
                "  Available participants:\n"
                "    - LaneFollower\n"
                "\n"
                "  Please note: All filenames must be absolute or relative to the location of the executable.\n"
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
            case DATABASE:
                settings.database = std::string(optarg);
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
                settings.featureSize = atoi(optarg);
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
                throw std::runtime_error("");
            }
        }
        return settings;
    }

} // namespace FeatureSetCreation
