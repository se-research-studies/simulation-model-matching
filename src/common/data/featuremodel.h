#pragma once

#include <cstdint>
#include <memory>

#include <FeatureSimulationCommon/Data/Correlation>
#include <FeatureSimulationCommon/Data/FeatureSet>

namespace Common {

  class FeatureModel {
  public:
    FeatureModel(const std::string& simulationName, const Correlation& correlation, uint16_t permutation, FeatureSet&& featureSet);
    FeatureModel(FeatureModel&& other);

  public:
    FeatureModel(const FeatureModel&) = delete;
    FeatureModel& operator=(const FeatureModel&) = delete;

  public:
    std::string getSimulationName() const;
    Correlation getCorrelation() const;
    uint16_t getPermutation() const;
    const FeatureSet& getFeatureSet() const;

  private:
    const std::string simulationName;
    const Correlation correlation;
    const uint16_t permutation = 0;
    FeatureSet featureSet;
  };

} // namespace FeatureExtraction

