#include "featuresettingsreader.h"

static const struct option featureSetCreationLongopts[] = {
    {"rec", required_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::REC_FILE},
    {"db", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::DATABASE},
    {"detector", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::DETECTOR},
    {"guiEnabled", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::USE_GUI},
    // ORB arguments
    {"nFeatures", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_N_FEATURES},
    {"scaleFactor", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_SCALE_FACTOR},
    {"nLevels", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_N_LEVELS},
    {"edgeThreshold", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_EDGE_THRESHOLD},
    {"firstLevel", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_FIRST_LEVEL},
    {"WTA_K", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_WTA_K},
    {"scoreType", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_SCORE_TYPE},
    {"patchSize", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_PATCH_SIZE},
    {"fastThreshold", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::ORB_FAST_THRESHOLD},
    // Lane detection arguments
    {"maxDistance", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_MAX_DISTANCE},
    {"firstThreshold", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_FIRST_THRESHOLD},
    {"secondThreshold", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_SECOND_THRESHOLD},
    {"apertureSize", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_APERTURE_SIZE},
    {"rho", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_RHO},
    {"theta", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_THETA},
    {"voteThreshold", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_VOTE_THRESHOLD},
    {"minLineLength", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_MIN_LINE_LENGTH},
    {"maxLineGap", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::LANE_MAX_LINE_GAP},
    // ShiTomasi arguments
    {"maxCorners", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::SHI_MAX_CORNERS},
    {"qualityLevel", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::SHI_QUALITY_LEVEL},
    {"minDistance", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::SHI_MIN_DISTANCE},
    {"blockSize", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::SHI_BLOCK_SIZE},
    {"useHarrisDetector", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::SHI_USE_HARRIS},
    {"kFree", optional_argument, nullptr, FeatureSetCreation::FeatureSettingsReader::SHI_K_FREE},
    {0, 0, 0, 0} //Required by getopt_long_only to mark the end of the arrays
};

namespace FeatureSetCreation {

    FeatureSettingsReader::FeatureSettingsReader() {
    }

    FeatureSettingsReader::~FeatureSettingsReader() {
    }

    void FeatureSettingsReader::printUsage(char* programName)
    {
        fprintf(stderr, "Usage: %s -rec='file' [-options]\n", programName);
        fprintf(stderr,
                "  -rec               Recording file.\n"
                "  -db                Optional. Database file. Default is ./data.sqlite.\n"
                "  -detector          Optional. Feature Detection Algorithm. Default is ORB.\n"
                "  -guiEnabled        Optional. Default is true\n"
                "  -nFeatures         Optional ORB parameter. Default is 500.\n"
                "  -scaleFactor       Optional ORB parameter. Default is 1.2\n"
                "  -nLevels           Optional ORB parameter. Default is 8\n"
                "  -edgeThreshold     Optional ORB parameter. Default is 31\n"
                "  -firstLevel        Optional ORB parameter. Default is 0\n"
                "  -WTA_K             Optional ORB parameter. Default is 2\n"
                "  -scoreType         Optional ORB parameter. Default is 0 (HARRIS_SCORE)\n"
                "  -patchSize         Optional ORB parameter. Default is 31\n"
                "  -fastThreshold     Optional ORB parameter. Default is 20\n"
                "  -maxDistance       Optional Lane Detection parameter. Default is 25\n"
                "  -firstThreshold    Optional Lane Detection parameter. Default is 100\n"
                "  -secondThreshold   Optional Lane Detection parameter. Default is 300\n"
                "  -apertureSize      Optional Lane Detection parameter. Default is 3\n"
                "  -rho               Optional Lane Detection parameter. Default is 1\n"
                "  -theta             Optional Lane Detection parameter. Default is Pi/180\n"
                "  -voteThreshold     Optional Lane Detection parameter. Default is 50\n"
                "  -minLineLength     Optional Lane Detection parameter. Default is 30\n"
                "  -maxLineGap        Optional Lane Detection parameter. Default is 20\n"
                "  -maxCorners        Optional ShiTomasi int parameter. Default is 100.\n"
                "  -qualityLevel      Optional ShiTomasi double parameter. Default is 0.5.\n"
                "  -minDistance       Optional ShiTomasi double parameter. Default is 0.5.\n"
                "  -blockSize         Optional ShiTomasi in parameter. Default is 3.\n"
                "  -useHarrisDetector Optional ShiTomasi boolean parameter. Default is F (false).\n"
                "  -kFree             Optional ShiTomasi double parameter. Default is 0.4.\n"
                "\n"
                "  Available detectors:\n"
                "    - ORB\n"
                "    - ShiTomasi\n"
                "\n"
                "  Please note: All filenames must be absolute or relative to the location of the executable.\n"
                );
    }

    Settings FeatureSettingsReader::readSettings(int argc, char* argv[])
    {
        Settings settings;
        int optIndex = 0;
        while ((optIndex = getopt_long_only(argc, argv, "", featureSetCreationLongopts, nullptr)) != -1) {
            switch (optIndex) {
            case REC_FILE:
                settings.recordingFile = std::string(optarg);
                break;
            case DATABASE:
                settings.database = std::string(optarg);
                break;
            case DETECTOR:
                settings.detectionAlg = std::string(optarg);
                break;
            case USE_GUI:
                settings.guiEnabled = atoi(optarg);
                break;
            case ORB_N_FEATURES:
                settings.orbSettings.nFeatures = atoi(optarg);
                break;
            case ORB_SCALE_FACTOR:
                settings.orbSettings.scaleFactor = atof(optarg);
                break;
            case ORB_N_LEVELS:
                settings.orbSettings.nLevels = atoi(optarg);
                break;
            case ORB_EDGE_THRESHOLD:
                settings.orbSettings.edgeThreshold = atoi(optarg);
                break;
            case ORB_FIRST_LEVEL:
                settings.orbSettings.firstLevel = atoi(optarg);
                break;
            case ORB_WTA_K:
                settings.orbSettings.WTA_K = atoi(optarg);
                break;
            case ORB_SCORE_TYPE:
                settings.orbSettings.scoreType = atoi(optarg);
                break;
            case ORB_PATCH_SIZE:
                settings.orbSettings.patchSize = atoi(optarg);
                break;
            case ORB_FAST_THRESHOLD:
                settings.orbSettings.fastThreshold = atoi(optarg);
                break;
            case LANE_MAX_DISTANCE:
                settings.laneDetectionSettings.maxDistance = atoi(optarg);
                break;
            case LANE_FIRST_THRESHOLD:
                settings.laneDetectionSettings.firstThreshold = atoi(optarg);
                break;
            case  LANE_SECOND_THRESHOLD:
                settings.laneDetectionSettings.secondThreshold = atoi(optarg);
                break;
            case LANE_APERTURE_SIZE:
                settings.laneDetectionSettings.apertureSize = atoi(optarg);
                break;
            case LANE_RHO:
                settings.laneDetectionSettings.rho = atoi(optarg);
                break;
            case LANE_THETA:
                settings.laneDetectionSettings.theta = atoi(optarg);
                break;
            case LANE_VOTE_THRESHOLD:
                settings.laneDetectionSettings.voteThreshold = atoi(optarg);
                break;
            case LANE_MIN_LINE_LENGTH:
                settings.laneDetectionSettings.minLineLength = atoi(optarg);
                break;
            case LANE_MAX_LINE_GAP:
                settings.laneDetectionSettings.maxLineGap = atoi(optarg);
                break;
            case SHI_MAX_CORNERS:
                settings.shiTomasiSettings.maxCorners = atoi(optarg);
                break;
            case SHI_QUALITY_LEVEL:
                settings.shiTomasiSettings.qualityLevel = atoi(optarg);
                break;
            case SHI_MIN_DISTANCE:
                settings.shiTomasiSettings.minDistance = atoi(optarg);
                break;
            case SHI_BLOCK_SIZE:
                settings.shiTomasiSettings.blockSize = atoi(optarg);
                break;
            case SHI_USE_HARRIS:
                if (atoi(optarg) != 0 && atoi(optarg) != 1) {
                    printUsage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                settings.shiTomasiSettings.useHarris = (atoi(optarg) == 1);
            case SHI_K_FREE:
                settings.shiTomasiSettings.kFree = atoi(optarg);
                break;
            default:
                printUsage(argv[0]);
                throw std::runtime_error("");
            }
        }
        return settings;
    }

} // namespace FeatureSetCreation
