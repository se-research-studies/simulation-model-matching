#pragma once

#include <memory>
#include <map>

#include <FeatureSimulationCommon/Data/Frame>
#include <FeatureSimulationCommon/Data/Region>

namespace Common {

  class FeatureSet {
  public:
    FeatureSet(const std::string recordingName);
    FeatureSet(FeatureSet&& other);

    FeatureSet(const FeatureSet&) = delete;

  public:
    std::string getRecordingName() const;
    size_t getFrameCount() const;
    Frame* getFrame(uint16_t index) const;
    const std::map<uint16_t, std::unique_ptr<Frame>>& getFrames() const;
    void addFrame(uint16_t index, std::unique_ptr<Frame> frame);

  private:
    const std::string recordingName;
    std::map<uint16_t, std::unique_ptr<Frame>> frames;
    std::vector<Region> regionsOfNoInterest;
  };

} // namespace FeatureExtraction

