#include "featuremodel.h"

namespace Common {

  FeatureModel::FeatureModel(const Correlation& correlation, uint16_t permutation)
    : correlation(correlation), permutation(permutation)
  {
  }

  FeatureModel::FeatureModel(FeatureModel&& other)
    : correlation(other.correlation), permutation(other.permutation), featureSet(move(other.featureSet))
  {
  }

} // namespace FeatureExtraction
