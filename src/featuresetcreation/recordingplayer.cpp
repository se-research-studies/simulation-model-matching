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
    }

    RecordingPlayer::~RecordingPlayer() {
    }

    cv::Size RecordingPlayer::imageSize() {
        if (hasNext()) {
            cv::Mat firstImage = next();
            player.rewind();
            return firstImage.size();
        } else {
            return cv::Size();
        }
    }

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
            odcore::data::image::SharedImage sharedImage = currentContainer.getData<odcore::data::image::SharedImage>();
            std::shared_ptr<odcore::wrapper::SharedMemory> memory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());
            IplImage* iplImage = cvCreateImage(cvSize(Common::Utils::to<int>(sharedImage.getWidth()), Common::Utils::to<int>(sharedImage.getHeight())), IPL_DEPTH_8U, sharedImage.getBytesPerPixel());
            memcpy(iplImage->imageData, memory->getSharedMemory(), sharedImage.getWidth() * sharedImage.getHeight() * sharedImage.getBytesPerPixel());
            cv::Mat image = cv::cvarrToMat(iplImage, true, true, 0);
            cvReleaseImage(&iplImage);
            return image;
        } else {
            return cv::Mat();
        }
    }

} // namespace FeatureSetCreation
