#pragma once

#include <memory>
#include <vector>

#include <FeatureSimulationCommon/Data/FeatureModel>

namespace Common {

  class Simulation {
  public:
    Simulation(const std::string& filename);

    Simulation(const Simulation&) = delete;

  private:
    const std::string filename;
    std::vector<FeatureModel> featureModels;
  };

} // namespace FeatureExtraction

