#include "frame.h"

#include <sstream>

#include <FeatureSimulationCommon/MakeUnique>

namespace Common {

  Frame::Frame(Frame&& other)
    : features(move(other.features)) {
  }

  std::string Frame::toString() const
  {
    std::string result;
    for (const Feature& feature : features) {
      result += feature.toString() + ";";
    }
    result.pop_back();
    return result;
  }

  std::unique_ptr<Frame> Frame::fromString(const std::string& stringFormatted)
  {
    std::unique_ptr<Frame> result = std::make_unique<Frame>();
    std::stringstream stream(stringFormatted);
    std::string featureString;
    while (std::getline(stream, featureString, ';')) {
      result->features.push_back(Feature::fromString(featureString));
    }
    return result;
  }

} // namespace FeatureExtraction
