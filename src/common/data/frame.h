#pragma once

#include <vector>

#include <FeatureSimulationCommon/Data/Feature>

namespace Common {

  struct Frame
  {
    Frame(Frame&& other);

    Frame(const Frame&) = delete;

    std::vector<Feature> features;
  };

} // namespace FeatureExtraction

