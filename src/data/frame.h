#pragma once

#include <memory>
#include <vector>

#include <DataManagement/Feature>

namespace FeatureExtraction {

  class Frame
  {
  public:
    Frame();
    virtual ~Frame();

  private:
    std::vector<std::unique_ptr<Feature>> features;
  };

} // namespace FeatureExtraction

