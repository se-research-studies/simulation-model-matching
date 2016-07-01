#pragma once

#include <getopt.h>

#include <FeatureSimulation/FeatureSetCreation/settings.h>

namespace FeatureSetCreation {

    class FeatureSettingsReader {
    public:
        FeatureSettingsReader();
        virtual ~FeatureSettingsReader();

    public:
        static void printUsage(char* programName);
        static Settings readSettings(int argc, char *argv[]);

    public:
        enum Argument {
            REC_FILE,
            DATABASE,
            DETECTOR,
            USE_GUI,
            ORB_N_FEATURES,
            ORB_SCALE_FACTOR,
            ORB_N_LEVELS,
            ORB_EDGE_THRESHOLD,
            ORB_FIRST_LEVEL,
            ORB_WTA_K,
            ORB_SCORE_TYPE,
            ORB_PATCH_SIZE,
            ORB_FAST_THRESHOLD,
            LANE_MAX_DISTANCE,
            LANE_FIRST_THRESHOLD,
            LANE_SECOND_THRESHOLD,
            LANE_APERTURE_SIZE,
            LANE_RHO,
            LANE_THETA,
            LANE_VOTE_THRESHOLD,
            LANE_MIN_LINE_LENGTH,
            LANE_MAX_LINE_GAP,
            SHI_MAX_CORNERS,
            SHI_QUALITY_LEVEL,
            SHI_MIN_DISTANCE,
            SHI_BLOCK_SIZE,
            SHI_USE_HARRIS,
            SHI_K_FREE
        };
    };

} // namespace FeatureSetCreation

