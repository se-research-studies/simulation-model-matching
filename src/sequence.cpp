#include "sequence.h"

namespace NoiseSimulation {

    Sequence::Sequence()
    {
    }
    Sequence::~Sequence()
    {
    }

    uint32_t Sequence::getStart() const
    {
        return start;
    }

    void Sequence::setStart(const uint32_t &value)
    {
        start = value;
    }

    uint32_t Sequence::getEnd() const
    {
        return end;
    }

    void Sequence::setEnd(const uint32_t &value)
    {
        end = value;
    }

    uint32_t Sequence::length() const
    {
        return end - start;
    }

} // namespace NoiseSimulation
