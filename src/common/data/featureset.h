#pragma once

#include <memory>
#include <map>

#include <FeatureSimulation/Common/Data/dirtyframe.h>
#include <FeatureSimulation/Common/Data/region.h>

namespace Common {

class FeatureSet {
public:
    FeatureSet(const std::string& recordingName);
    FeatureSet(FeatureSet&& other) = default;

public:
    FeatureSet(const FeatureSet&) = delete;
    FeatureSet& operator=(const FeatureSet&) = delete;

public:
    std::string getRecordingName() const;
    size_t getFrameCount() const;
    uint32_t getFirstFrame() const;
    uint32_t getLastFrame() const;
    const DirtyFrame& getFrame(uint32_t index) const;
    const std::map<uint32_t, DirtyFrame>& getFrames() const;
    void addFrame(uint32_t index, DirtyFrame&& frame);

private:
    const std::string recordingName;
    std::map<uint32_t, DirtyFrame> frames;
};

} // namespace FeatureExtraction

