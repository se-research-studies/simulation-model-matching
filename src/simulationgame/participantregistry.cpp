#include "participantregistry.h"

namespace SimulationGame {

    ParticipantRegistry::ParticipantRegistry(const std::string& cid, const std::string& freq, uint32_t frameLimit)
        : cid(cid), freq(freq), frameLimit(frameLimit)
    {
    }

    ParticipantRegistry::~ParticipantRegistry()
    {
    }


} // namespace SimulationGame
