#pragma once

#include <Data/FeatureSet>

namespace FeatureExtraction {

  class FeatureSetDAO
  {
  public:
    FeatureSetDAO();
    virtual ~FeatureSetDAO();

  public:
    std::unique_ptr<FeatureSet> load(const std::string recordingFilename);
    void save(FeatureSet& featureSet);
  };

} // namespace FeatureExtraction

