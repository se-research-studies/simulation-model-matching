#include "recordingsection.h"

namespace Common {

    RecordingSection::RecordingSection(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame)
        : recordingName(recordingName), startFrame(startFrame), endFrame(endFrame) {
    }

    std::string RecordingSection::getRecordingName() const
    {
        return recordingName;
    }

    uint32_t RecordingSection::getStartFrame() const
    {
        return startFrame;
    }

    uint32_t RecordingSection::getEndFrame() const
    {
        return endFrame;
    }

} // namespace Common
