#include <iostream>

#include <getopt.h>

#include <FeatureSimulation/FeatureSetCreation/featuresetcreator.h>
#include <FeatureSimulation/FeatureSetCreation/settings.h>
#include <FeatureSimulation/FeatureSetCreation/settingsvalidator.h>

enum Argument {
    REC_FILE,
    DETECTOR,
    USE_GUI,
    ORB_N_FEATURES,
    ORB_SCALE_FACTOR,
    ORB_N_LEVELS,
    ORB_EDGE_THRESHOLD,
    ORB_FIRST_LEVEL,
    ORB_WTA_K,
    ORB_SCORE_TYPE,
    ORB_PATCH_SIZE,
    ORB_FAST_THRESHOLD,
    LANE_FUZZINESS_FACTOR,
    LANE_FIRST_THRESHOLD,
    LANE_SECOND_THRESHOLD,
    LANE_APERTURE_SIZE,
    LANE_RHO,
    LANE_THETA,
    LANE_VOTE_THRESHOLD,
    LANE_MIN_LINE_LENGTH,
    LANE_MAX_LINE_GAP,
    SHI_MAX_CORNERS,
    SHI_QUALITY_LEVEL,
    SHI_MIN_DISTANCE,
    SHI_BLOCK_SIZE,
    SHI_USE_HARRIS,
    SHI_K_FREE
};

static const struct option longopts[] = {
    // Operation arguments
    {"rec", required_argument, nullptr, REC_FILE},
    {"detector", optional_argument, nullptr, DETECTOR},
    {"guiEnabled", optional_argument, nullptr, USE_GUI},
    // ORB arguments
    {"nFeatures", optional_argument, nullptr, ORB_N_FEATURES},
    {"scaleFactor", optional_argument, nullptr, ORB_SCALE_FACTOR},
    {"nLevels", optional_argument, nullptr, ORB_N_LEVELS},
    {"edgeThreshold", optional_argument, nullptr, ORB_EDGE_THRESHOLD},
    {"firstLevel", optional_argument, nullptr, ORB_FIRST_LEVEL},
    {"WTA_K", optional_argument, nullptr, ORB_WTA_K},
    {"scoreType", optional_argument, nullptr, ORB_SCORE_TYPE},
    {"patchSize", optional_argument, nullptr, ORB_PATCH_SIZE},
    {"fastThreshold", optional_argument, nullptr, ORB_FAST_THRESHOLD},
    // Lane detection arguments
    {"fuzzinessFactor", optional_argument, nullptr, LANE_FUZZINESS_FACTOR},
    {"firstThreshold", optional_argument, nullptr, LANE_FIRST_THRESHOLD},
    {"secondThreshold", optional_argument, nullptr, LANE_SECOND_THRESHOLD},
    {"apertureSize", optional_argument, nullptr, LANE_APERTURE_SIZE},
    {"rho", optional_argument, nullptr, LANE_RHO},
    {"theta", optional_argument, nullptr, LANE_THETA},
    {"voteThreshold", optional_argument, nullptr, LANE_VOTE_THRESHOLD},
    {"minLineLength", optional_argument, nullptr, LANE_MIN_LINE_LENGTH},
    {"maxLineGap", optional_argument, nullptr, LANE_MAX_LINE_GAP},
    // ShiTomasi arguments
    {"maxCorners", optional_argument, nullptr, SHI_MAX_CORNERS},
    {"qualityLevel", optional_argument, nullptr, SHI_QUALITY_LEVEL},
    {"minDistance", optional_argument, nullptr, SHI_MIN_DISTANCE},
    {"blockSize", optional_argument, nullptr, SHI_BLOCK_SIZE},
    {"useHarrisDetector", optional_argument, nullptr, SHI_USE_HARRIS},
    {"kFree", optional_argument, nullptr, SHI_K_FREE},
    {0, 0, 0, 0} //Required by getopt_long_only to mark the end of the arrays
};

void printUsage(char* programName) {
    fprintf(stderr, "Usage: %s -rec='file' [-options]\n", programName);
    fprintf(stderr,
            "  -rec               Recording file.\n"
            "  -detector          Optional. Feature Detection Algorithm. Supported are: ORB. Default is ORB.\n"
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
            "  -fuzzinessFactor   Optional Lane Detection parameter. Default is 1.0\n"
            "  -firstThreshold    Optional Lane Detection parameter. Default is 100\n"
            "  -secondThreshold   Optional Lane Detection parameter. Default is 400\n"
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
           );
}

int main(int argc, char *argv[]) {
    int optIndex = 0;

    FeatureSetCreation::Settings settings;

    while ((optIndex = getopt_long_only(argc, argv, "", longopts, nullptr)) != -1) {
        switch (optIndex) {
        case REC_FILE:
            settings.recordingFile = std::string(optarg);
            break;
        case DETECTOR:
            settings.detectionAlg = std::string(optarg);
            break;
        case USE_GUI:
            settings.guiEnabled = optarg;
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
        case LANE_FUZZINESS_FACTOR:
            settings.laneDetectionSettings.fuzzinessFactor = atoi(optarg);
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
            exit(EXIT_FAILURE);
        }
    }

    // Hardcoded settings for debugging purposes
    settings.recordingFile = "../resources/straightroad.rec";
    //settings.detectionAlg = "ShiTomasi";
    //settings.guiEnabled = false;
    //settings.laneDetectionSettings.fuzzinessFactor = 1.5;
//  settings.laneDetectionSettings.minLineLength = 5;
//  settings.laneDetectionSettings.firstThreshold = 50;
//  settings.laneDetectionSettings.secondThreshold = 275;

    try {
        FeatureSetCreation::SettingsValidator validator;
        validator.validate(settings);
        FeatureSetCreation::FeatureSetCreator featureSetCreator(settings);
        featureSetCreator.createFeatureSet();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    exit(EXIT_SUCCESS);
}
