#include "gamerunner.h"

#include <future>
#include <iostream>

#include <FeatureSimulation/SimulationGame/abstractparticipant.h>
#include <FeatureSimulation/SimulationGame/participantregistry.h>
#include <FeatureSimulation/SimulationGame/settings.h>

namespace SimulationGame {

    GameRunner::GameRunner(SimulationGame::ParticipantRegistry& registry)
        : registry(registry) {
    }

    GameRunner::~GameRunner() {
    }

    int GameRunner::start(const Settings& settings)
    {
        std::cout << "Press ENTER to start and again enter to stop before frame limit is reached... " << std::endl;
        waitForEnter();

        std::vector<Common::LocalFeatureSets> permutations = createPermutations(settings.correlationFile);

        int result;
        for (Common::LocalFeatureSets& permutation : permutations) {
            control.start(settings.cid, settings.freq, settings.configurationFile);
            result = runSimulation(settings, std::move(permutation));
            control.stop();
            if (result != odcore::data::dmcp::ModuleExitCodeMessage::OKAY) {
                break;
            }
        }

        return result;
    }

    void GameRunner::waitForEnter()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter pressed..." << std::endl;
    }

    int GameRunner::runSimulation(const Settings& settings, Common::LocalFeatureSets&& permutation)
    {
        std::unique_ptr<AbstractParticipant> participant = registry.getParticipant(settings.participant);
        std::future<odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode> simulation =
                std::async(std::launch::async, &AbstractParticipant::runModule, participant.get(), settings, std::move(permutation));
        std::future<void> enterKey = std::async(std::launch::async, &GameRunner::waitForEnter);
        while (simulation.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
            if (enterKey.wait_for(std::chrono::milliseconds(10)) == std::future_status::ready) {
                participant->forceQuit();
            }
        }
        if (enterKey.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
            std::cout << "Done. Press enter to quit." << std::endl;
        } else {
            std::cout << "Done." << std::endl;
        }
        return simulation.get();
    }

    std::vector<Common::LocalFeatureSets> GameRunner::createPermutations(const std::string& correlationFile) const
    {
        std::vector<Common::LocalFeatureSets> result;
        std::vector<Common::Correlation> correlations = correlationDao.load(correlationFile);
        std::vector<uint8_t> correlationSectionIndexes(correlations.size(), 0);
        do {
            Common::LocalFeatureSets localFeatureSets;
            for (size_t correlationIndex = 0; correlationIndex < correlations.size(); ++correlationIndex) {
                const Common::Correlation& correlation = correlations.at(correlationIndex);
                const Common::RecordingSection& recordingSection = correlation.getSections().at(correlationSectionIndexes.at(correlationIndex));
                std::unique_ptr<Common::FeatureSet> features = featureSetDao.load(recordingSection.getRecordingName(), recordingSection.getStartFrame(), recordingSection.getEndFrame());
                localFeatureSets.emplace(correlation.getRectangle(), std::move(features));
            }
            result.push_back(std::move(localFeatureSets));
        } while (adaptCorrelationSectionIndexes(correlations, correlationSectionIndexes));

        return result;
    }

    bool GameRunner::adaptCorrelationSectionIndexes(const std::vector<Common::Correlation>& correlations, std::vector<uint8_t>& correlationSectionIndexes) const
    {
        bool result = true;
        for (size_t correlationIndex = 0; correlationIndex < correlations.size(); ++correlationIndex) {
            bool goToNeighbour = false;
            if (correlationSectionIndexes.at(correlationIndex) < correlations.at(correlationIndex).getSections().size() - 1) {
                ++correlationSectionIndexes[correlationIndex];
            } else {
                correlationSectionIndexes[correlationIndex] = 0;
                goToNeighbour = true;
            }
            if (goToNeighbour) {
                if (correlationIndex == correlations.size() - 1) {
                    result = false;
                    break;
                }
            } else {
                break;
            }
        }
        return result;
    }


} // namespace SimulationGame
