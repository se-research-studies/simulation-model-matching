#include "featureset.h"

namespace Common {

  FeatureSet::FeatureSet(const std::string recordingName)
    : recordingName(recordingName)
  {
  }

  FeatureSet::FeatureSet(FeatureSet&& other)
    : recordingName(other.recordingName), frames(move(other.frames)), regionsOfNoInterest(move(other.regionsOfNoInterest))
  {
  }

} // namespace FeatureExtraction
