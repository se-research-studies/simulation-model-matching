#pragma once

#include <opencv2/core/core.hpp>

#include <opendavinci/odtools/player/Player.h>

namespace FeatureSetCreation {

    class RecordingPlayer {
    public:
        RecordingPlayer(std::string recordingFile);
        virtual ~RecordingPlayer();

    public:
        cv::Size imageSize() const;
        bool hasNext();
        cv::Mat next();

    private:
        void initMetaData();
        std::shared_ptr<odcore::wrapper::SharedMemory> extractSharedMemoryFromContainer();

    private:
        int imageWidth = 0;
        int imageHeight = 0;
        int bytesPerPixel = 0;
        odtools::player::Player player;
        odcore::data::Container currentContainer;

    private:
        uint32_t MEMSEGMENT_SIZE = 2800000;
        uint32_t NUM_MEMSEGMENTS = 20;
    };

} // namespace FeatureSetCreation

