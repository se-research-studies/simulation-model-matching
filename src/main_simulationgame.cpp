#include <iostream>

#include <FeatureSimulation/Common/DataManagement/database.h>

#include <FeatureSimulation/SimulationGame/autopilotregistry.h>
#include <FeatureSimulation/SimulationGame/gamerunner.h>
#include <FeatureSimulation/SimulationGame/settings.h>
#include <FeatureSimulation/SimulationGame/settingsreader.h>

#include <FeatureSimulation/SimulationGame/Autopilots/lanefollower.h>

int main(int argc, char *argv[]) {
    try {
        SimulationGame::Settings settings = SimulationGame::SimSettingsReader::readSettings(argc, argv);
        Common::Database::getInstance().setDbFilename(argv[0], settings.database);

        SimulationGame::AutopilotRegistry registry(settings.cid, settings.freq);
        registry.registerAutopilot<SimulationGame::LaneFollower>("LaneFollower");

        SimulationGame::GameRunner gameRunner(registry);
        gameRunner.start(settings);

        exit(EXIT_SUCCESS);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
