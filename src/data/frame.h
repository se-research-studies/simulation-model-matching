#pragma once

#include <vector>

#include <Data/Feature>

namespace FeatureExtraction {

  struct Frame
  {
    Frame(Frame&& other);

    Frame(const Frame& other) = delete;

    std::vector<Feature> features;
  };

} // namespace FeatureExtraction

