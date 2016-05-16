#include "recordingplayer.h"

#include <opencv2/imgproc/imgproc.hpp>

#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

#include <FeatureSimulation/Common/MakeUnique>
#include <FeatureSimulation/Common/Utils>

namespace FeatureSetCreation {

    RecordingPlayer::RecordingPlayer(std::string recordingFile)
        : player(odcore::io::URL("file://" + recordingFile), false, MEMSEGMENT_SIZE, NUM_MEMSEGMENTS, false) {
        initMetaData();
    }

    RecordingPlayer::~RecordingPlayer() {
    }

    void RecordingPlayer::initMetaData() {
        if (hasNext()) {
            odcore::data::image::SharedImage sharedImage = currentContainer.getData<odcore::data::image::SharedImage>();
            imageWidth = Common::Utils::to<int>(sharedImage.getWidth());
            imageHeight = Common::Utils::to<int>(sharedImage.getHeight());
            bytesPerPixel = Common::Utils::to<int>(sharedImage.getBytesPerPixel());
        }
        player.rewind();
    }

    cv::Size RecordingPlayer::imageSize() const {
        return cv::Size(imageWidth, imageHeight);
    }

    // The odtools::player::Player interface does not allow checking if the remaining data contains an image, so to find out if
    // there is another image the player has to be moved forwards until an image is found.
    // So to create an iterator-like interface the hasNext() method has to move the player to the next image.
    bool RecordingPlayer::hasNext() {
        while (player.hasMoreData()) {
            currentContainer = player.getNextContainerToBeSent();
            if (currentContainer.getDataType() == odcore::data::image::SharedImage::ID()) {
                return true;
            }
        }
        return false;
    }

    cv::Mat RecordingPlayer::next() {
        if (currentContainer.getDataType() == odcore::data::image::SharedImage::ID()) {
            std::shared_ptr<odcore::wrapper::SharedMemory> memory = extractSharedMemoryFromContainer();
            return cv::Mat(imageSize(), CV_MAKETYPE(CV_8U, bytesPerPixel), memory->getSharedMemory()).clone();
        } else {
            return cv::Mat();
        }
    }

    std::shared_ptr<odcore::wrapper::SharedMemory> RecordingPlayer::extractSharedMemoryFromContainer() {
        odcore::data::image::SharedImage sharedImage = currentContainer.getData<odcore::data::image::SharedImage>();
        return odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());
    }

} // namespace FeatureSetCreation
