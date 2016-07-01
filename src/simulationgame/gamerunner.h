#pragma once

#include <FeatureSimulation/Common/Data/permutation.h>
#include <FeatureSimulation/Common/DataManagement/correlationdao.h>
#include <FeatureSimulation/Common/DataManagement/featuresetdao.h>

#include <FeatureSimulation/SimulationGame/odvcontrol.h>

namespace SimulationGame {

    class ParticipantRegistry;
    struct Settings;

    class GameRunner {
    public:
        GameRunner(SimulationGame::ParticipantRegistry& registry);
        virtual ~GameRunner();

    public:
        int start(const Settings& settings);
        
    private:
        static void waitForEnter();
        int runSimulation(const Settings& settings, Common::LocalFeatureSets&& permutation);
        int runSimulationWithFrameLimit(const Settings& settings, Common::LocalFeatureSets&& permutation);
        int runSimulationWithEnterKeyDetection(const Settings& settings, Common::LocalFeatureSets&& permutation);
        std::vector<Common::LocalFeatureSets> createPermutations(const std::string& correlationFilename) const;
        std::vector<Common::LocalFeatureSets> createPermutationWithoutFeatures() const;
        std::vector<Common::LocalFeatureSets> convertCorrelationsToPermutations(const std::string& correlationFilename) const;
        bool adaptCorrelationSectionIndexes(const std::vector<Common::Correlation>& correlations, std::vector<uint8_t>& correlationSectionIndexes) const;

    private:
        SimulationGame::ParticipantRegistry& registry;
        OdvControl control;
        Common::CorrelationDAO correlationDao;
        Common::FeatureSetDAO featureSetDao;
    };

} // namespace SimulationGame

