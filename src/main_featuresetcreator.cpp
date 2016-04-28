#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 5) {
      std::cerr << "Usage: " << argv[0] << " -fm=DETECTIONALG -nFeatures=NFEATURES -edgeThreshold=EDGETHRESHOLD -in=RECORDING" << std::endl;
      exit(EXIT_FAILURE);
  }

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


  exit(EXIT_SUCCESS);
}
