#include "featureset.h"

namespace Common {

  FeatureSet::FeatureSet(const std::string recordingName)
    : recordingName(recordingName) {
  }

  FeatureSet::FeatureSet(FeatureSet&& other)
    : recordingName(other.recordingName), frames(move(other.frames)), regionsOfNoInterest(move(other.regionsOfNoInterest)) {
  }

  std::string FeatureSet::getRecordingName() const {
    return recordingName;
  }

  size_t FeatureSet::getFrameCount() const {
    return frames.size();
  }

  Frame* FeatureSet::getFrame(uint32_t index) const {
    return frames.at(index).get();
  }

  const std::map<uint32_t, std::unique_ptr<Frame>>& FeatureSet::getFrames() const {
    return frames;
  }

  void FeatureSet::addFrame(uint32_t index, std::unique_ptr<Frame> frame) {
    frames.insert(std::make_pair(index, move(frame)));
  }

} // namespace FeatureExtraction
