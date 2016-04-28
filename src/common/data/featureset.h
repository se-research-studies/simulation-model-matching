#pragma once

#include <memory>
#include <map>

#include <FeatureSimulationCommon/Data/Frame>
#include <FeatureSimulationCommon/Data/Region>

namespace Common {

  class FeatureSet {
  public:
    FeatureSet(const std::string recordingName);
    FeatureSet(FeatureSet&& other) = default;

  public:
    FeatureSet(const FeatureSet&) = delete;
    Feature& operator=(const FeatureSet&) = delete;

  public:
    std::string getRecordingName() const;
    size_t getFrameCount() const;
    const Frame& getFrame(uint32_t index) const;
    const std::map<uint32_t, Frame>& getFrames() const;
    void addFrame(uint32_t index, Frame&& frame);

  private:
    const std::string recordingName;
    std::map<uint32_t, Frame> frames;
    std::vector<Region> regionsOfNoInterest;
  };

} // namespace FeatureExtraction

