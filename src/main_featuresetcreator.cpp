#include <iostream>

#include <getopt.h>

#include <FeatureSimulation/FeatureSetCreation/FeatureSetCreator>

static const struct option longopts[] = {
  {"rec", required_argument, nullptr, 1},
  {"guiEnabled", optional_argument, nullptr, 2},
  {"nFeatures", optional_argument, nullptr, 3},
  {"scaleFactor", optional_argument, nullptr, 4},
  {"nLevels", optional_argument, nullptr, 5},
  {"edgeThreshold", optional_argument, nullptr, 6},
  {"firstLevel", optional_argument, nullptr, 7},
  {"WTA_K", optional_argument, nullptr, 8},
  {"scoreType", optional_argument, nullptr, 9},
  {"patchSize", optional_argument, nullptr, 10},
  {"fastThreshold", optional_argument, nullptr, 11},
  {0, 0, 0 ,0}
};

void printUsage(char* programName) {
  fprintf(stderr, "Usage: %s -rec='file' [-options]\n", programName);
  fprintf(stderr,
          "  -rec             Recording file.\n"
          "  -guiEnabled      Optional. Default is true\n"
          "  -nFeatures       Optional ORB parameter. Default is 500.\n"
          "  -scaleFactor     Optional ORB parameter. Default is 1.2\n"
          "  -nLevels         Optional ORB parameter. Default is 8\n"
          "  -edgeThreshold   Optional ORB parameter. Default is 31\n"
          "  -firstLevel      Optional ORB parameter. Default is 0\n"
          "  -WTA_K           Optional ORB parameter. Default is 2\n"
          "  -scoreType       Optional ORB parameter. Default is 0 (HARRIS_SCORE)\n"
          "  -patchSize       Optional ORB parameter. Default is 31\n"
          "  -fastThreshold   Optional ORB parameter. Default is 20\n");
}

int main(int argc, char *argv[]) {

  int optIndex = 0;

  std::string recordingFile;
  bool guiEnabled = true;
  int nFeatures = 500;
  float scaleFactor = 1.2f;
  int nLevels = 8;
  int edgeThreshold = 31;
  int firstLevel = 0;
  int WTA_K = 2;
  int scoreType = cv::ORB::HARRIS_SCORE;
  int patchSize = 31;
  int fastThreshold = 20;

  while ((optIndex = getopt_long_only(argc, argv, "", longopts, nullptr)) != -1) {
    switch (optIndex) {
    case 1:
      recordingFile = std::string(optarg);
      break;
    case 2:
      guiEnabled = optarg;
      break;
    case 3:
      nFeatures = atoi(optarg);
      break;
    case 4:
      scaleFactor = atof(optarg);
      break;
    case 5:
      nLevels = atoi(optarg);
      break;
    case 6:
      edgeThreshold = atoi(optarg);
      break;
    case 7:
      firstLevel = atoi(optarg);
      break;
    case 8:
      WTA_K = atoi(optarg);
      break;
    case 9:
      scoreType = atoi(optarg);
      break;
    case 10:
      patchSize = atoi(optarg);
      break;
    case 11:
      fastThreshold = atoi(optarg);
      break;
    default:
      printUsage(argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  recordingFile = "/home/sebastian/Uni/Bachelorarbeit/Code/resources/straightroad.rec";
  try {
    FeatureSetCreation::FeatureSetCreator featureSetCreator;
    featureSetCreator.init("ORB", recordingFile, guiEnabled, nFeatures, scaleFactor, nLevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize, fastThreshold);
    featureSetCreator.createFeatureSet();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  exit(EXIT_SUCCESS);
}
