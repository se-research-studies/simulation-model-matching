#include "featureset.h"

namespace Common {

  FeatureSet::FeatureSet(const std::string recordingName)
    : recordingName(recordingName) {
  }

  std::string FeatureSet::getRecordingName() const {
    return recordingName;
  }

  size_t FeatureSet::getFrameCount() const {
    return frames.size();
  }

  const DirtyFrame& FeatureSet::getFrame(uint32_t index) const {
    if (frames.count(index) == 0) {
      throw std::out_of_range("There is no frame with index " + std::to_string(index));
    }
    return frames.at(index);
  }

  const std::map<uint32_t, DirtyFrame>& FeatureSet::getFrames() const {
    return frames;
  }

  void FeatureSet::addFrame(uint32_t index, DirtyFrame&& frame) {
    frames.insert(std::make_pair(index, std::move(frame)));
  }

} // namespace FeatureExtraction
