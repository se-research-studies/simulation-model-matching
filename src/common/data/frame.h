#pragma once

#include <memory>
#include <vector>

#include <FeatureSimulationCommon/Data/Feature>

namespace Common {

  class Frame {
  public:
    Frame() = default;
    Frame(Frame&& other);

    Frame(const Frame&) = delete;

  public:
    std::string toString() const;
    static std::unique_ptr<Frame> fromString(const std::string& stringFormatted);

  public:
    std::vector<Feature> features;
  };

} // namespace FeatureExtraction

