#pragma once

#include <cstdint>
#include <memory>

#include <FeatureSimulationCommon/Data/Correlation>
#include <FeatureSimulationCommon/Data/FeatureSet>

namespace Common {

  struct FeatureModel
  {
    FeatureModel(const Correlation& correlation, uint16_t permutation);
    FeatureModel(FeatureModel&& other);

    FeatureModel(const FeatureModel&) = delete;

    const Correlation correlation;
    const uint16_t permutation = 0;
    std::unique_ptr<FeatureSet> featureSet;
  };

} // namespace FeatureExtraction

