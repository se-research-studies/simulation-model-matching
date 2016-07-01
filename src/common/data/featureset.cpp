#include "featureset.h"

namespace Common {

FeatureSet::FeatureSet(const std::string& recordingName)
    : recordingName(recordingName), emptyFrame(DirtyFrame()) {
}

std::string FeatureSet::getRecordingName() const {
    return recordingName;
}

size_t FeatureSet::getFrameCount() const {
    return frames.size();
}

uint32_t FeatureSet::getFirstFrame() const
{
    return frames.cbegin()->first;
}

uint32_t FeatureSet::getLastFrame() const
{
    return (--frames.cend())->first;
}

const DirtyFrame& FeatureSet::getFrame(uint32_t index) const {
    if (frames.count(index) == 0) {
        return emptyFrame;
    } else {
        return frames.at(index);
    }
}

const std::map<uint32_t, DirtyFrame>& FeatureSet::getFrames() const {
    return frames;
}

void FeatureSet::addFrame(uint32_t index, DirtyFrame&& frame) {
    frames.insert(std::make_pair(index, std::move(frame)));
}

} // namespace FeatureExtraction
