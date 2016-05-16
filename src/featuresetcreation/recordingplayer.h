#pragma once

#include <opencv2/core/core.hpp>

#include <opendavinci/odtools/player/Player.h>

namespace FeatureSetCreation {

    class RecordingPlayer {
    public:
        RecordingPlayer(std::string recordingFile);
        virtual ~RecordingPlayer();

    public:
        cv::Size imageSize();
        bool hasNext();
        cv::Mat next();

    private:
        odtools::player::Player player;
        odcore::data::Container currentContainer;

    private:
        uint32_t MEMSEGMENT_SIZE = 2800000;
        uint32_t NUM_MEMSEGMENTS = 20;
    };

} // namespace FeatureSetCreation

