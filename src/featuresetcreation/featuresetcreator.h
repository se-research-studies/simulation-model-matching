#pragma once

#include <FeatureSimulation/Common/Data/FeatureSet>

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>
#include <FeatureSimulation/FeatureSetCreation/FeatureDetectorORB>

namespace FeatureSetCreation {

  class FeatureSetCreator {
  public:
    FeatureSetCreator();
    virtual ~FeatureSetCreator();

  public:
    template <typename... Settings> void init(const std::string detectionMethod, Settings&&... settings) {
      if (detectionMethod == "ORB") {
        featureDetector.reset(new FeatureDetectorORB(std::forward<Settings>(settings)...));
      }
    }

  public:
    void createFeatureSet(const std::string& recordingName);

  private:
    uint32_t PLAYER_MEMORYSEGMENT_SIZE = 2800000;
    uint32_t PLAYER_NUMBER_OF_MEMORY_SEGMENTS = 20;

    std::unique_ptr<FeatureDetector> featureDetector;
  };

} // namespace FeatureCreation

