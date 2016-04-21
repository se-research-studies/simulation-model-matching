#include "featuresetdao.h"

namespace FeatureExtraction {

  FeatureSetDAO::FeatureSetDAO()
  {
  }

  FeatureSetDAO::~FeatureSetDAO()
  {
  }

  std::unique_ptr<FeatureSet> FeatureSetDAO::load(const std::string recordingFilename)
  {
    std::unique_ptr<FeatureSet> result;
    return result;
  }

  void FeatureSetDAO::save(FeatureSet& featureSet)
  {

  }

} // namespace FeatureExtraction
