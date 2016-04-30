#pragma once

#include <opendavinci/odtools/player/Player.h>

#include <FeatureSimulation/Common/Data/FeatureSet>
#include <FeatureSimulation/Common/DataManagement/FeatureSetDAO>
#include <FeatureSimulation/Common/DataManagement/RoniDAO>

#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>
#include <FeatureSimulation/FeatureSetCreation/FeatureDetectorORB>

namespace FeatureSetCreation {

  class FeatureSetCreator {
  public:
    FeatureSetCreator();
    virtual ~FeatureSetCreator();

  public:
    template <typename... Settings> void init(const std::string detectionMethod, const std::string& recordingName, Settings&&... settings) {
      this->recordingName = recordingName;
      if (detectionMethod == "ORB") {
        featureDetector.reset(new FeatureDetectorORB(std::forward<Settings>(settings)...));
        featureDetector->validateSettings();
      }
    }

  public:
    void createFeatureSet();

  private:
    cv::Mat createMaskFromRonis(odtools::player::Player& player) const;
    std::vector<Common::Region> loadRonis() const;
    cv::Size getImageSize(odtools::player::Player& player) const;
    cv::Mat readNextImage(odcore::data::Container container) const;
    void saveFeatureSet(const Common::FeatureSet& featureSet) const;

  private:
    uint32_t PLAYER_MEMORYSEGMENT_SIZE = 2800000;
    uint32_t PLAYER_NUMBER_OF_MEMORY_SEGMENTS = 20;

  private:
    std::string recordingName;

    std::unique_ptr<FeatureDetector> featureDetector;
    Common::FeatureSetDAO featureSetDao;
    Common::RoniDAO roniDao;
  };

} // namespace FeatureCreation

