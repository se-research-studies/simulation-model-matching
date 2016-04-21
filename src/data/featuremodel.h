#pragma once

#include <cstdint>
#include <memory>

#include <Data/Correlation>
#include <Data/FeatureSet>

namespace FeatureExtraction {

  struct FeatureModel
  {
    FeatureModel(const Correlation& correlation, uint16_t permutation);
    FeatureModel(FeatureModel&& other);

    FeatureModel(const FeatureModel& other) = delete;

    const Correlation correlation;
    const uint16_t permutation = 0;
    std::unique_ptr<FeatureSet> featureSet;
  };

} // namespace FeatureExtraction

