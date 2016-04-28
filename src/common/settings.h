#pragma once

#include <stdint.h>
#include <string>

namespace Common {

  class Settings {
  public:
    Settings();
    virtual ~Settings();

  public:
    std::string getFeatureMatcher() const;
    uint16_t getMaxFeatures() const;
    uint16_t getEdgeThreshold() const;

  private:
    const std::string featureMatcher;
    const uint16_t maxFeatures = 0;
    const uint16_t edgeThreshold = 0;
  };

} // namespace Common

