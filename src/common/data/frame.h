#pragma once

#include <memory>
#include <vector>

#include <FeatureSimulation/Common/Data/Feature>

namespace Common {

  class Frame {
  public:
    Frame(std::vector<Feature>&& features);
    Frame() = default;
    Frame(Frame&& other) = default;

  public:
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

  public:    
    const std::vector<Feature>& getFeatures() const;
    uint32_t getFeatureCount() const;
    void addFeature(Feature&& feature);

    std::string toString() const;
    static Frame fromString(const std::string& stringFormatted);

  private:
    std::vector<Feature> features;
  };

} // namespace FeatureExtraction

