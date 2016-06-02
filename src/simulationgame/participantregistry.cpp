#include "participantregistry.h"

namespace SimulationGame {

    ParticipantRegistry::ParticipantRegistry(std::string&& cid, std::string&& freq)
        : cid(cid), freq(freq)
    {
    }

    ParticipantRegistry::~ParticipantRegistry()
    {
    }


} // namespace SimulationGame
