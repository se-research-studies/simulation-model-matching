#include <iostream>

#include <getopt.h>

#include <FeatureSimulation/FeatureSetCreation/FeatureSetCreator>
#include <FeatureSimulation/FeatureSetCreation/Settings>
#include <FeatureSimulation/FeatureSetCreation/SettingsValidator>

static const struct option longopts[] = {
  {"rec", required_argument, nullptr, 0},
  {"detector", optional_argument, nullptr, 1},
  {"guiEnabled", optional_argument, nullptr, 2},
  {"detector", required_argument, nullptr, 2},
  {"nFeatures", optional_argument, nullptr, 3},
  {"scaleFactor", optional_argument, nullptr, 4},
  {"nLevels", optional_argument, nullptr, 5},
  {"edgeThreshold", optional_argument, nullptr, 6},
  {"firstLevel", optional_argument, nullptr, 7},
  {"WTA_K", optional_argument, nullptr, 8},
  {"scoreType", optional_argument, nullptr, 9},
  {"patchSize", optional_argument, nullptr, 10},
  {"fastThreshold", optional_argument, nullptr, 11},
  {"firstThreshold", optional_argument, nullptr, 12},
  {"secondThreshold", optional_argument, nullptr, 13},
  {"apertureSize", optional_argument, nullptr, 14},
  {"rho", optional_argument, nullptr, 15},
  {"theta", optional_argument, nullptr, 16},
  {"voteThreshold", optional_argument, nullptr, 17},
  {"minLineLength", optional_argument, nullptr, 18},
  {"maxLineGap", optional_argument, nullptr, 19},
  {0, 0, 0 ,0}
};

void printUsage(char* programName) {
  fprintf(stderr, "Usage: %s -rec='file' [-options]\n", programName);
  fprintf(stderr,
          "  -rec             Recording file.\n"
          "  -detector        Optional. Feature Detection Algorithm. Supported are: ORB. Default is ORB.\n"
          "  -guiEnabled      Optional. Default is true\n"
          "  -nFeatures       Optional ORB parameter. Default is 500.\n"
          "  -scaleFactor     Optional ORB parameter. Default is 1.2\n"
          "  -nLevels         Optional ORB parameter. Default is 8\n"
          "  -edgeThreshold   Optional ORB parameter. Default is 31\n"
          "  -firstLevel      Optional ORB parameter. Default is 0\n"
          "  -WTA_K           Optional ORB parameter. Default is 2\n"
          "  -scoreType       Optional ORB parameter. Default is 0 (HARRIS_SCORE)\n"
          "  -patchSize       Optional ORB parameter. Default is 31\n"
          "  -fastThreshold   Optional ORB parameter. Default is 20\n"
          "  -firstThreshold  Optional Lane Detection parameter. Default is 100\n"
          "  -secondThreshold Optional Lane Detection parameter. Default is 400\n"
          "  -apertureSize    Optional Lane Detection parameter. Default is 3\n"
          "  -rho             Optional Lane Detection parameter. Default is 1\n"
          "  -theta           Optional Lane Detection parameter. Default is Pi/180\n"
          "  -voteThreshold   Optional Lane Detection parameter. Default is 50\n"
          "  -minLineLength   Optional Lane Detection parameter. Default is 30\n"
          "  -maxLineGap      Optional Lane Detection parameter. Default is 20\n");
}

int main(int argc, char *argv[]) {

  int optIndex = 0;

  FeatureSetCreation::Settings settings;

  while ((optIndex = getopt_long_only(argc, argv, "", longopts, nullptr)) != -1) {
    switch (optIndex) {
    case 0:
      settings.recordingFile = std::string(optarg);
      break;
    case 1:
      settings.detectionAlg = std::string(optarg);
      break;
    case 2:
      settings.guiEnabled = optarg;
      break;
    case 3:
      settings.orbSettings.nFeatures = atoi(optarg);
      break;
    case 4:
      settings.orbSettings.scaleFactor = atof(optarg);
      break;
    case 5:
      settings.orbSettings.nLevels = atoi(optarg);
      break;
    case 6:
      settings.orbSettings.edgeThreshold = atoi(optarg);
      break;
    case 7:
      settings.orbSettings.firstLevel = atoi(optarg);
      break;
    case 8:
      settings.orbSettings.WTA_K = atoi(optarg);
      break;
    case 9:
      settings.orbSettings.scoreType = atoi(optarg);
      break;
    case 10:
      settings.orbSettings.patchSize = atoi(optarg);
      break;
    case 11:
      settings.orbSettings.fastThreshold = atoi(optarg);
      break;
    case 12:
      settings.laneDetectionSettings.firstThreshold = atoi(optarg);
      break;
    case 13:
      settings.laneDetectionSettings.secondThreshold = atoi(optarg);
      break;
    case 14:
      settings.laneDetectionSettings.apertureSize = atoi(optarg);
      break;
    case 15:
      settings.laneDetectionSettings.rho = atoi(optarg);
      break;
    case 16:
      settings.laneDetectionSettings.theta = atoi(optarg);
      break;
    case 17:
      settings.laneDetectionSettings.voteThreshold = atoi(optarg);
      break;
    case 18:
      settings.laneDetectionSettings.minLineLength = atoi(optarg);
      break;
    case 19:
      settings.laneDetectionSettings.maxLineGap = atoi(optarg);
      break;
    default:
      printUsage(argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  settings.recordingFile = "/home/sebastian/Uni/Bachelorarbeit/Code/resources/straightroad.rec";
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
