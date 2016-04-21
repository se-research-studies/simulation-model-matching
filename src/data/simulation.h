#pragma once

#include <memory>
#include <vector>

#include <Data/FeatureModel>

namespace FeatureExtraction {

  struct Simulation
  {
    Simulation(const std::string& filename);
    Simulation(Simulation&& other);

    Simulation(const Simulation& other) = delete;

    const std::string filename;
    std::vector<std::unique_ptr<FeatureModel>> featureModels;
  };

} // namespace FeatureExtraction

