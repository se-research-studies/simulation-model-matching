#include "dirtyframe.h"

#include <sstream>

#include <FeatureSimulation/Common/MakeUnique>

namespace Common {

  DirtyFrame::DirtyFrame(std::vector<Feature>&& features)
    : features(features) {
  }

  const std::vector<Feature>& DirtyFrame::getFeatures() const {
    return features;
  }

  uint32_t DirtyFrame::getFeatureCount() const {
    return features.size();
  }

  void DirtyFrame::addFeature(Feature&& feature) {
    features.push_back(feature);
  }

  std::string DirtyFrame::toSqlString() const {
    std::string result;
    for (const Feature& feature : features) {
      result += feature.toSqlString() + ";";
    }
    result.pop_back();
    return result;
  }

  DirtyFrame DirtyFrame::fromSqlString(const std::string& stringFormatted) {
    std::stringstream stream(stringFormatted);
    std::string featureString;
    std::vector<Feature> features;
    while (std::getline(stream, featureString, ';')) {
      features.push_back(Feature::fromSqlString(featureString));
    }
    return DirtyFrame(move(features));
  }
  
} // namespace FeatureExtraction
