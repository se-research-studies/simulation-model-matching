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
        std::cout << "Press ENTER to start... " << std::endl;
        waitForEnter();

        int result;
        for (uint32_t i = 0; i < settings.repetitions; ++i) {
            std::cout << "Running repetition " << i + 1 << " of " << settings.repetitions << std::endl;
            std::vector<Common::LocalFeatureSets> permutations;
            if (settings.correlationFile.size() > 0) {
                permutations = createPermutations(settings.correlationFile);
            } else {
                permutations.push_back(Common::LocalFeatureSets());
            }
            for (size_t permutation = 0; permutation < permutations.size(); ++permutation) {
                std::cout << "Running permutation " << permutation + 1 << " of " << permutations.size() << std::endl;
                control.start(settings.cid, settings.freq, settings.configurationFile);
                result = runSimulation(settings, std::move(permutations.at(permutation)));
                control.stop();
                if (result != odcore::data::dmcp::ModuleExitCodeMessage::OKAY) {
                    std::cout << "An OpenDaVinci error occured. Exit code: " << result << std::endl;
                    return result;
                }
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
        int result;
        if (settings.frameLimit == 0) {
            result = runSimulationWithEnterKeyDetection(settings, move(permutation));
        } else {
            result = runSimulationWithFrameLimit(settings, move(permutation));
        }
        std::cout << "Done." << std::endl;
        return result;
    }

    int GameRunner::runSimulationWithFrameLimit(const Settings& settings, Common::LocalFeatureSets&& permutation)
    {
        std::unique_ptr<AbstractParticipant> participant = registry.getParticipant(settings.participant);
        std::future<odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode> simulation =
                std::async(std::launch::async, &AbstractParticipant::runModule, participant.get(), settings, std::move(permutation));
        while (simulation.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
        }
        return simulation.get();
    }

    int GameRunner::runSimulationWithEnterKeyDetection(const Settings& settings, Common::LocalFeatureSets&& permutation)
    {
        std::unique_ptr<AbstractParticipant> participant = registry.getParticipant(settings.participant);
        std::future<odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode> simulation =
                std::async(std::launch::async, &AbstractParticipant::runModule, participant.get(), settings, std::move(permutation));
        std::future<void> enterKey = std::async(std::launch::async, &GameRunner::waitForEnter);
        while (enterKey.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
        }
        participant->forceQuit();
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
