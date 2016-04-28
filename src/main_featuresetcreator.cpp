#include <iostream>

#include <FeatureSimulation/FeatureSetCreation/FeatureSetCreator>

int main(int argc, char *argv[]) {
//  if (argc != 5) {
//      std::cerr << "Usage: " << argv[0] << " -fm=DETECTIONALG -nFeatures=LIMIT -edgeThreshold=EDGETHRESHOLD -in=RECORDING" << std::endl;
//      exit(EXIT_FAILURE);
//  }

//  std::string videoFilename;
//  std::string simulationFilename;

//  int opt;
//  while ((opt = getopt(argc, argv, "v:s:")) != -1) {
//      switch (opt) {
//      case 'v':
//          videoFilename = optarg;
//          break;
//      case 's':
//          simulationFilename = optarg;
//          break;
//      default:
//          break;
//      }
//  }

//  std::clog << "Using video " << videoFilename << " and sim " << simulationFilename << std::endl;

  // Create FeatureDetector depending on argument fm
  // Open recording
  // Iterate over frames
  // Detect features in every frame, add Frame to FeatureSet
  // Save FeatureSet

  try {
    FeatureSetCreation::FeatureSetCreator featureSetCreator;
    featureSetCreator.createFeatureSet("/home/sebastian/Uni/Bachelorarbeit/Code/bin/straightroad.rec");
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  exit(EXIT_SUCCESS);
}
