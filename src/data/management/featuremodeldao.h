#pragma once

#include <Data/FeatureModel>

namespace FeatureExtraction {

  class FeatureModelDAO
  {
  public:
    FeatureModelDAO();
    virtual ~FeatureModelDAO();

  public:
    std::vector<std::unique_ptr<FeatureModel>> load(const std::string& simulationFilename);
    void save(FeatureModel& featureModel);
  };

} // namespace FeatureExtraction

