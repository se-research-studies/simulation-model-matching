#pragma once

#include <memory>
#include <unordered_map>

#include <Data/Frame>
#include <Data/Region>

namespace FeatureExtraction {

  struct FeatureSet
  {
    FeatureSet(const std::string recordingName);
    FeatureSet(FeatureSet&& other);

    FeatureSet(const FeatureSet& other) = delete;

    const std::string recordingName;
    std::unordered_map<uint16_t, std::unique_ptr<Frame>> frames;
    std::vector<Region> regionsOfNoInterest;
  };

} // namespace FeatureExtraction

