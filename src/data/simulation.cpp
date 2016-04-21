#include "simulation.h"

namespace FeatureExtraction {

  Simulation::Simulation(const std::string& filename)
    : filename(filename)
  {
  }

  Simulation::Simulation(Simulation&& other)
    : filename(other.filename), featureModels(move(other.featureModels))
  {
  }

} // namespace FeatureExtraction
