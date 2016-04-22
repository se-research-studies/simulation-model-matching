#pragma once

#include <memory>
#include <vector>

#include <FeatureSimulationCommon/Data/FeatureModel>

namespace Common {

  struct Simulation
  {
    Simulation(const std::string& filename);
    Simulation(Simulation&& other);

    Simulation(const Simulation&) = delete;

    const std::string filename;
    std::vector<std::unique_ptr<FeatureModel>> featureModels;
  };

} // namespace FeatureExtraction

