#pragma once

#include <opencv2/features2d/features2d.hpp>

namespace FeatureSetCreation {

  struct OrbSettings {
    int nFeatures = 500;
    float scaleFactor = 1.2f;
    int nLevels = 8;
    int edgeThreshold = 31;
    int firstLevel = 0;
    int WTA_K = 2;
    int scoreType = cv::ORB::HARRIS_SCORE;
    int patchSize = 31;
    int fastThreshold = 20;
  };

  struct LaneDetectionSettings {
    uint16_t maxDistance = 25;
    double firstThreshold = 100;
    double secondThreshold = 400;
    int apertureSize = 3;
    double rho = 1;
    double theta = CV_PI/180;
    int voteThreshold = 50;
    double minLineLength = 30;
    double maxLineGap = 20;
  };

  struct ShiTomasiSettings {
      int maxCorners = 100;
      double qualityLevel = 0.5;
      double minDistance = 0.5;
      int blockSize = 3;
      bool useHarris = false;
      double kFree = 0.4;
  };

  struct Settings {
    std::string recordingFile;
    std::string detectionAlg = "ORB";
    bool guiEnabled = true;
    OrbSettings orbSettings;
    LaneDetectionSettings laneDetectionSettings;
    ShiTomasiSettings shiTomasiSettings;
  };

} // namespace FeatureSetCreation
