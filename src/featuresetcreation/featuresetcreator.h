#pragma once

#include <FeatureSimulation/Common/Data/FeatureSet>

namespace FeatureSetCreation {

  class FeatureSetCreator {
  public:
    FeatureSetCreator();
    virtual ~FeatureSetCreator();

  public:
    void createFeatureSet(const std::string& recordingName);

  private:
    uint32_t PLAYER_MEMORYSEGMENT_SIZE = 2800000;
    uint32_t PLAYER_NUMBER_OF_MEMORY_SEGMENTS = 20;
  };

} // namespace FeatureCreation

