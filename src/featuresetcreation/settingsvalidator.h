#pragma once

#include <FeatureSimulation/FeatureSetCreation/Settings>

namespace FeatureSetCreation {

  class SettingsValidator {
  public:
    SettingsValidator();
    virtual ~SettingsValidator();

  public:
    void validate(const Settings& settings) const;

  private:
    std::string validateOrbSettings(const OrbSettings& settings) const;
    std::string validateLaneDetectionSettings(const LaneDetectionSettings& settings) const;
  };

} // namespace FeatureSetCreation


