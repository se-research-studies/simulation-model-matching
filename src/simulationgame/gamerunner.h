#pragma once

#include <FeatureSimulation/Common/Data/permutation.h>
#include <FeatureSimulation/Common/DataManagement/correlationdao.h>
#include <FeatureSimulation/Common/DataManagement/featuresetdao.h>

#include <FeatureSimulation/SimulationGame/odvcontrol.h>

namespace SimulationGame {

    class AutopilotRegistry;
    struct Settings;

    class GameRunner {
    public:
        GameRunner(SimulationGame::AutopilotRegistry& registry);
        virtual ~GameRunner();

    public:
        int start(const Settings& settings);
        
    private:
        static void waitForEnter();
        int runSimulation(const Settings& settings, Common::Permutation&& permutation);
        int runSimulationWithFrameLimit(const Settings& settings, Common::Permutation&& permutation);
        int runSimulationWithEnterKeyDetection(const Settings& settings, Common::Permutation&& permutation);
        std::vector<Common::Permutation> createPermutations(const std::string& correlationFilename) const;
        std::vector<Common::Permutation> createEmptyPermutation() const;
        std::vector<Common::Permutation> convertCorrelationsToPermutations(const std::string& correlationFilename) const;
        bool adaptRecordingSectionIndexes(const std::vector<Common::Correlation>& correlations, std::vector<uint8_t>& recordingSectionIndexes) const;
        std::string recordingSectionIndexesToString(const std::vector<uint8_t>& recordingSectionIndexes) const;

    private:
        SimulationGame::AutopilotRegistry& registry;
        OdvControl control;
        Common::CorrelationDAO correlationDao;
        Common::FeatureSetDAO featureSetDao;
    };

} // namespace SimulationGame

