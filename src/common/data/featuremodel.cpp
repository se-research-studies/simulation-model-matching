#include "featuremodel.h"

namespace Common {

  FeatureModel::FeatureModel(const std::string& simulationName, const Correlation& correlation, uint16_t permutation, std::unique_ptr<FeatureSet> featureSet)
    : simulationName(simulationName), correlation(correlation), permutation(permutation), featureSet(move(featureSet)) {
  }

  FeatureModel::FeatureModel(FeatureModel&& other)
    : simulationName(other.simulationName), correlation(other.correlation), permutation(other.permutation), featureSet(move(other.featureSet)) {
  }

} // namespace FeatureExtraction
