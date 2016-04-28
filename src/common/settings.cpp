#include "settings.h"

namespace Common {

  Settings::Settings()
  {
  }

  Settings::~Settings()
  {
  }
  
  std::string Settings::getFeatureMatcher() const
  {
      return featureMatcher;
  }
  
  uint16_t Settings::getMaxFeatures() const
  {
      return maxFeatures;
  }
  
  uint16_t Settings::getEdgeThreshold() const
  {
      return edgeThreshold;
  }
  
} // namespace Common
