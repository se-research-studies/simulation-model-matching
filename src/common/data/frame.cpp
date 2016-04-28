#include "frame.h"

#include <sstream>

#include <FeatureSimulationCommon/MakeUnique>

namespace Common {

  Frame::Frame(std::vector<Feature>&& features)
    : features(features) {
  }

  const std::vector<Feature>& Frame::getFeatures() const {
    return features;
  }

  uint32_t Frame::getFeatureCount() const {
    return features.size();
  }

  void Frame::addFeature(Feature&& feature) {
    features.push_back(feature);
  }

  std::string Frame::toString() const {
    std::string result;
    for (const Feature& feature : features) {
      result += feature.toString() + ";";
    }
    result.pop_back();
    return result;
  }

  Frame Frame::fromString(const std::string& stringFormatted) {
    std::stringstream stream(stringFormatted);
    std::string featureString;
    std::vector<Feature> features;
    while (std::getline(stream, featureString, ';')) {
      features.push_back(Feature::fromString(featureString));
    }
    return Frame(move(features));
  }
  
} // namespace FeatureExtraction
