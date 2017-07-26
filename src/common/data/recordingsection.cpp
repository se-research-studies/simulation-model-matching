#include "recordingsection.h"

namespace Common {

    RecordingSection::RecordingSection(const std::string& _recordingName, uint32_t _startFrame, uint32_t _endFrame)
        : recordingName(_recordingName), startFrame(_startFrame), endFrame(_endFrame) {
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
