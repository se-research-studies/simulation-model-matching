#pragma once

#include <memory>
#include <vector>

#include <Data/Region>

namespace FeatureExtraction {

  class RoniDAO
  {
  public:
    RoniDAO();
    virtual ~RoniDAO();

  public:
    std::vector<Region> load(const std::string recordingFilename);
  };

} // namespace FeatureExtraction

