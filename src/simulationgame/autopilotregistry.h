#pragma once

#include <functional>
#include <string>
#include <map>

#include <FeatureSimulation/SimulationGame/abstractautopilot.h>

namespace SimulationGame {

    class AutopilotRegistry
    {
    public:
        AutopilotRegistry(const std::string& cid, const std::string& freq);
        virtual ~AutopilotRegistry();

    public:
        template <typename T>
        void registerAutopilot(const std::string& name) {
            autopilots[name] = &AbstractAutopilot::createInstance<T>;
        }

        std::unique_ptr<AbstractAutopilot> getAutopilot(std::string name) {
            const int argc = 3;
            std::string cidArg = "--cid=" + cid;
            std::string freqArg = "--freq=" + freq;
            char* argv[] = { &name[0], &cidArg[0], &freqArg[0], nullptr };
            return autopilots.at(name)(argc, argv);
        }

    private:
        std::string cid;
        std::string freq;
        std::map<std::string, std::function<std::unique_ptr<AbstractAutopilot>(int, char*[])>> autopilots;
    };

} // namespace SimulationGame

