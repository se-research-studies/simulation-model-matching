#pragma once

#include <memory>
#include <unordered_map>

#include <DataManagement/Frame>

namespace FeatureExtraction {

  class Simulation
  {
  public:
    Simulation();
    virtual ~Simulation();

  private:
    std::unordered_map<uint32_t, std::unique_ptr<Frame>> frames;

  };

} // namespace FeatureExtraction

