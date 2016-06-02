#include "abstractparticipant.h"

namespace SimulationGame {

    AbstractParticipant::AbstractParticipant(int argc, char** argv, const std::string& name)
        : odcore::base::module::TimeTriggeredConferenceClientModule(argc, argv, name)
    {
    }

    AbstractParticipant::~AbstractParticipant()
    {
    }

    void AbstractParticipant::setUp()
    {

    }

    void AbstractParticipant::tearDown()
    {

    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::body()
    {
        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }


} // namespace SimulationGame
