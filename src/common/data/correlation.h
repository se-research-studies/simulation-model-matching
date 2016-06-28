#pragma once

#include <vector>

#include <FeatureSimulation/Common/Data/rectangle.h>
#include <FeatureSimulation/Common/Data/recordingsection.h>

namespace Common {

    class Correlation {
    public:
        Correlation(const Rectangle& rectangle);

    public:
        void addSection(RecordingSection&& section);
        const Rectangle& getRectangle() const;
        const std::vector<RecordingSection>& getSections() const;

    private:
        Rectangle rectangle;
        std::vector<RecordingSection> sections;
    };

} // namespace Common

