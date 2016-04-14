#include "recording.h"

namespace NoiseSimulation {

    Recording::Recording()
    {
    }

    Recording::~Recording()
    {
    }

    std::string Recording::getFilename() const
    {
        return filename;
    }

} // namespace NoiseExtractor
