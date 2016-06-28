#include "correlation.h"

namespace Common {

    Correlation::Correlation(const Rectangle& rectangle)
        : rectangle(rectangle)
    {
    }

    void Correlation::addSection(RecordingSection&& section)
    {
        sections.push_back(std::move(section));
    }

    const Rectangle& Correlation::getRectangle() const
    {
        return rectangle;
    }

    const std::vector<RecordingSection>& Correlation::getSections() const
    {
        return sections;
    }

} // namespace Common
