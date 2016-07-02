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
        int result = odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        for (uint32_t i = 0; i < settings.repetitions; ++i) {
            std::cout << "Running repetition " << i + 1 << " of " << settings.repetitions << std::endl;
            std::vector<Common::Permutation> permutations = createPermutations(settings.correlationFile);
            for (size_t permutation = 0; permutation < permutations.size(); ++permutation) {
                std::cout << "Running permutation " << permutation + 1 << " of " << permutations.size() << std::endl;
                result = runSimulation(settings, std::move(permutations.at(permutation)));
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

    int GameRunner::runSimulation(const Settings& settings, Common::Permutation&& permutation)
    {
        control.start(settings.cid, settings.freq, settings.configurationFile);
        int result;
        if (settings.frameLimit == 0) {
            result = runSimulationWithEnterKeyDetection(settings, std::move(permutation));
        } else {
            result = runSimulationWithFrameLimit(settings, std::move(permutation));
        }
        control.stop();
        std::cout << "Done." << std::endl;
        return result;
    }

    int GameRunner::runSimulationWithFrameLimit(const Settings& settings, Common::Permutation&& permutation)
    {
        std::unique_ptr<AbstractParticipant> participant = registry.getParticipant(settings.participant);
        std::future<odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode> simulation =
                std::async(std::launch::async, &AbstractParticipant::runModule, participant.get(), settings, std::move(permutation));
        while (simulation.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
        }
        return simulation.get();
    }

    int GameRunner::runSimulationWithEnterKeyDetection(const Settings& settings, Common::Permutation&& permutation)
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

    std::vector<Common::Permutation> GameRunner::createPermutations(const std::string& correlationFilename) const
    {
        if (correlationFilename.size() == 0) {
            return createPermutationWithoutFeatures();
        } else {
            return convertCorrelationsToPermutations(correlationFilename);
        }
    }

    std::vector<Common::Permutation> GameRunner::createPermutationWithoutFeatures() const
    {
        std::vector<Common::Permutation> result;
        result.push_back(Common::Permutation());
        return result;
    }

    std::vector<Common::Permutation> GameRunner::convertCorrelationsToPermutations(const std::string& correlationFilename) const
    {
        std::vector<Common::Permutation> result;
        std::vector<Common::Correlation> correlations = correlationDao.load(correlationFilename);
        std::vector<uint8_t> recordingSectionIndexes(correlations.size(), 0);
        do {
            Common::Permutation permutation;
            for (size_t correlationIndex = 0; correlationIndex < correlations.size(); ++correlationIndex) {
                const uint8_t recordingSectionIndex = recordingSectionIndexes.at(correlationIndex);
                const Common::Correlation& correlation = correlations.at(correlationIndex);
                const Common::RecordingSection& recordingSection = correlation.getSections().at(recordingSectionIndex);
                std::unique_ptr<Common::FeatureSet> features = featureSetDao.load(recordingSection.getRecordingName(), recordingSection.getStartFrame(), recordingSection.getEndFrame());
                permutation.localFeatureSets.emplace(correlation.getRectangle(), std::move(features));
                permutation.index = recordingSectionIndexesToString(recordingSectionIndexes);
            }
            result.push_back(std::move(permutation));
        } while (adaptRecordingSectionIndexes(correlations, recordingSectionIndexes));
        return result;
    }

    bool GameRunner::adaptRecordingSectionIndexes(const std::vector<Common::Correlation>& correlations, std::vector<uint8_t>& recordingSectionIndexes) const
    {
        bool result = true;
        for (size_t correlationIndex = 0; correlationIndex < correlations.size(); ++correlationIndex) {
            bool goToNeighbour = false;
            if (recordingSectionIndexes.at(correlationIndex) < correlations.at(correlationIndex).getSections().size() - 1) {
                ++recordingSectionIndexes[correlationIndex];
            } else {
                recordingSectionIndexes[correlationIndex] = 0;
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

    std::string GameRunner::recordingSectionIndexesToString(const std::vector<uint8_t>& recordingSectionIndexes) const
    {
        std::string result;
        if (recordingSectionIndexes.size() > 0) {
            for (uint8_t index : recordingSectionIndexes) {
                result += std::to_string(index) + ",";
            }
            result.pop_back();
        }
        return result;
    }


} // namespace SimulationGame
