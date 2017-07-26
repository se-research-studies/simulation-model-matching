#include "autopilotregistry.h"

namespace SimulationGame {

    AutopilotRegistry::AutopilotRegistry(const std::string& _cid, const std::string& _freq)
        : cid(_cid), freq(_freq) {
    }

    AutopilotRegistry::~AutopilotRegistry() {
    }


} // namespace SimulationGame
