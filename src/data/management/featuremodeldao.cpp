#include "featuremodeldao.h"

namespace FeatureExtraction {

  FeatureModelDAO::FeatureModelDAO()
  {
  }

  FeatureModelDAO::~FeatureModelDAO()
  {
  }

  std::vector<std::unique_ptr<FeatureModel>> FeatureModelDAO::load(const std::string& simulationFilename)
  {
    std::vector<std::unique_ptr<FeatureModel>> result;
    return result;
  }

  void FeatureModelDAO::save(FeatureModel& featureModel)
  {

  }

} // namespace FeatureExtraction
