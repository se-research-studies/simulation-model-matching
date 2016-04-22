#pragma once

#include <FeatureSimulationCommon/Data/FeatureSet>

namespace Common {

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

