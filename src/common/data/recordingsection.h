#pragma once

#include <cstdint>
#include <string>

namespace Common {

    class RecordingSection {
    public:
        RecordingSection(const std::string& _recordingName, uint32_t _startFrame, uint32_t _endFrame);
        RecordingSection(RecordingSection&& other) = default;
        RecordingSection(const RecordingSection& other) = default;

    public:
        std::string getRecordingName() const;
        uint32_t getStartFrame() const;
        uint32_t getEndFrame() const;

    private:
        std::string recordingName;
        uint32_t startFrame;
        uint32_t endFrame;
    };

} // namespace Common

