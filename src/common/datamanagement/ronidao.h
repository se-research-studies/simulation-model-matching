#pragma once

#include <memory>
#include <vector>

#include <FeatureSimulationCommon/Data/Region>

namespace Common {

  class RoniDAO
  {
  public:
    RoniDAO();
    virtual ~RoniDAO();

  public:
    std::vector<Region> load(const std::string recordingFilename);
  };

} // namespace FeatureExtraction

