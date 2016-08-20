#include "autopilotregistry.h"

namespace SimulationGame {

    AutopilotRegistry::AutopilotRegistry(const std::string& cid, const std::string& freq)
        : cid(cid), freq(freq)
    {
    }

    AutopilotRegistry::~AutopilotRegistry()
    {
    }


} // namespace SimulationGame
