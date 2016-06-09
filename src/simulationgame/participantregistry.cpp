#include "participantregistry.h"

namespace SimulationGame {

    ParticipantRegistry::ParticipantRegistry(const std::string& cid, const std::string& freq)
        : cid(cid), freq(freq)
    {
    }

    ParticipantRegistry::~ParticipantRegistry()
    {
    }


} // namespace SimulationGame
