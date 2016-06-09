#pragma once

#include <functional>
#include <string>
#include <map>

#include <FeatureSimulation/SimulationGame/abstractparticipant.h>

namespace SimulationGame {

    class ParticipantRegistry
    {
    public:
        ParticipantRegistry(const std::string& cid, const std::string& freq);
        virtual ~ParticipantRegistry();

    public:
        template <typename T>
        void registerParticipant(const std::string& name) {
            participants[name] = &AbstractParticipant::createInstance<T>;
        }

        std::unique_ptr<AbstractParticipant> getParticipant(std::string name) {
            const int argc = 3;
            std::string cidArg = "--cid=" + cid;
            std::string freqArg = "--freq=" + freq;
            char* argv[] = { &name[0], &cidArg[0], &freqArg[0], nullptr };
            return participants.at(name)(argc, argv);
        }

    private:
        std::string cid;
        std::string freq;
        std::map<std::string, std::function<std::unique_ptr<AbstractParticipant>(int, char*[])>> participants;
    };

} // namespace SimulationGame

