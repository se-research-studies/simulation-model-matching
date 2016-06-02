#pragma once

#include <opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h>

namespace SimulationGame {

    class AbstractParticipant : public odcore::base::module::TimeTriggeredConferenceClientModule
    {
    public:
        AbstractParticipant(int argc, char** argv, const std::string& name);
        virtual ~AbstractParticipant();

    public:
        template <typename SubClass> static AbstractParticipant&& createInstance(int argc, char** argv) {
            return SubClass(argc, argv);
        }

        void setUp() override;
        void tearDown() override;
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() override;
    };

} // namespace SimulationGame

