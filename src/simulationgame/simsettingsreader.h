#pragma once

#include <getopt.h>

#include <FeatureSimulation/SimulationGame/settings.h>

namespace SimulationGame {

    class SimSettingsReader {
    public:
        static void printUsage(char* programName);
        static Settings readSettings(int argc, char *argv[]);

    public:
        enum Argument {
            CID,
            FREQ,
            DATABASE,
            CONFIG_FILE,
            ID,
            AUTOPILOT,
            FRAME_LIMIT,
            FEATURE_SCALE,
            FEATURE_SIZE,
            CORRELATION_FILE,
            SHOW_GUI,
            REPETITIONS
        };
    };

} // namespace FeatureSetCreation

