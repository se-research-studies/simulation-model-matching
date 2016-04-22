#pragma once

#include <memory>
#include <unordered_map>

#include <FeatureSimulationCommon/Data/Frame>
#include <FeatureSimulationCommon/Data/Region>

namespace Common {

  struct FeatureSet
  {
    FeatureSet(const std::string recordingName);
    FeatureSet(FeatureSet&& other);

    FeatureSet(const FeatureSet&) = delete;

    const std::string recordingName;
    std::unordered_map<uint16_t, std::unique_ptr<Frame>> frames;
    std::vector<Region> regionsOfNoInterest;
  };

} // namespace FeatureExtraction

