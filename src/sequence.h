#pragma once

#include <cstdint>

namespace NoiseSimulation {

    class Sequence
    {
    public:
        Sequence();
        virtual ~Sequence();

    public:
        uint32_t getStart() const;
        void setStart(const uint32_t &value);

        uint32_t getEnd() const;
        void setEnd(const uint32_t &value);

        uint32_t length() const;

    private:
        uint32_t start = 0;
        uint32_t end = 0;

    };

} // namespace NoiseSimulation

