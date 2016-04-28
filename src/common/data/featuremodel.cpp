#include "featuremodel.h"

namespace Common {

  FeatureModel::FeatureModel(const std::string& simulationName, const Correlation& correlation, uint16_t permutation, FeatureSet&& featureSet)
    : simulationName(simulationName), correlation(correlation), permutation(permutation), featureSet(std::move(featureSet)) {
  }

  FeatureModel::FeatureModel(FeatureModel&& other)
    : simulationName(std::move(other.simulationName)), correlation(std::move(other.correlation)), permutation(other.permutation), featureSet(std::move(other.featureSet)) {
  }
  
  std::string FeatureModel::getSimulationName() const {
      return simulationName;
  }
  
  Correlation FeatureModel::getCorrelation() const {
      return correlation;
  }
  
  uint16_t FeatureModel::getPermutation() const {
      return permutation;
  }

  const FeatureSet& FeatureModel::getFeatureSet() const {
    return featureSet;
  }

} // namespace FeatureExtraction
