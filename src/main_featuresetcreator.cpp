#include <iostream>

#include <getopt.h>

#include <FeatureSimulation/FeatureSetCreation/FeatureSetCreator>
#include <FeatureSimulation/FeatureSetCreation/Settings>
#include <FeatureSimulation/FeatureSetCreation/SettingsValidator>

static const struct option longopts[] = {
  // Operation arguments
  {"rec", required_argument, nullptr, 0},
  {"detector", optional_argument, nullptr, 1},
  {"guiEnabled", optional_argument, nullptr, 2},
  {"detector", required_argument, nullptr, 2}, //XXX Why is detector included twice?
  // ORB arguments
  {"nFeatures", optional_argument, nullptr, 3},
  {"scaleFactor", optional_argument, nullptr, 4},
  {"nLevels", optional_argument, nullptr, 5},
  {"edgeThreshold", optional_argument, nullptr, 6},
  {"firstLevel", optional_argument, nullptr, 7},
  {"WTA_K", optional_argument, nullptr, 8},
  {"scoreType", optional_argument, nullptr, 9},
  {"patchSize", optional_argument, nullptr, 10},
  {"fastThreshold", optional_argument, nullptr, 11},
  // Lane detection arguments
  {"firstThreshold", optional_argument, nullptr, 12},
  {"secondThreshold", optional_argument, nullptr, 13},
  {"apertureSize", optional_argument, nullptr, 14},
  {"rho", optional_argument, nullptr, 15},
  {"theta", optional_argument, nullptr, 16},
  {"voteThreshold", optional_argument, nullptr, 17},
  {"minLineLength", optional_argument, nullptr, 18},
  {"maxLineGap", optional_argument, nullptr, 19},
  // ShiTomasi arguments
  {"maxCorners", optional_argument, nullptr, 20},
  {"qualityLevel", optional_argument, nullptr, 21},
  {"minDistance", optional_argument, nullptr, 22},
  {"blockSize", optional_argument, nullptr, 23},
  {"useHarrisDetector", optional_argument, nullptr, 24},
  {"kFree", optional_argument, nullptr, 25},
  {0, 0, 0 ,0} //XXX What is this used for?
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

int main(int argc, char *argv[]) {

  int optIndex = 0;

  FeatureSetCreation::Settings settings;

  while ((optIndex = getopt_long_only(argc, argv, "", longopts, nullptr)) != -1) {
    switch (optIndex) {
    case REC_FILE:
      std::cout << "Found argument REC_FILE =" << std::string(optarg) << std::endl;
      settings.recordingFile = std::string(optarg);
      break;
    case DETECTOR:
      std::cout << "Found argument DETECTOR =" << std::string(optarg) << std::endl;
      settings.detectionAlg = std::string(optarg);
      break;
    case USE_GUI:
      std::cout << "Found argument USE_GUI =" << std::string(optarg) << std::endl;
      settings.guiEnabled = optarg;
      break;
    case ORB_N_FEATURES:
      std::cout << "Found argument USE_GUI =" << std::string(optarg) << std::endl;
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

  settings.recordingFile = "/home/ubuntu/Workspace/simulation-model-matching/resources/straightroad.rec";
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
