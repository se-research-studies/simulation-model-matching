#include "featuresetcreator.h"

#include <opencv2/core/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>

#include <opendavinci/odtools/player/Player.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

#include <FeatureSimulation/Common/Utils>
#include <FeatureSimulation/Common/DataManagement/FeatureSetDAO>
#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>

namespace FeatureSetCreation {

  FeatureSetCreator::FeatureSetCreator() {
  }

  FeatureSetCreator::~FeatureSetCreator() {
  }

  void FeatureSetCreator::createFeatureSet() {
    Common::FeatureSet result(recordingName);
    odcore::io::URL url("file://" + recordingName);
    odtools::player::Player player(url, false, PLAYER_MEMORYSEGMENT_SIZE, PLAYER_NUMBER_OF_MEMORY_SEGMENTS, false);

    // TODO: Ronis laden und in Maske umwandeln

    for (int i = 0; player.hasMoreData(); ++i) {
      odcore::data::Container container = player.getNextContainerToBeSent();
      if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
        odcore::data::image::SharedImage sharedImage = container.getData<odcore::data::image::SharedImage>();

        std::shared_ptr<odcore::wrapper::SharedMemory> memory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());

        IplImage* iplImage = cvCreateImage(cvSize(Common::Utils::to<int>(sharedImage.getWidth()), Common::Utils::to<int>(sharedImage.getHeight())), IPL_DEPTH_8U, sharedImage.getBytesPerPixel());

        memcpy(iplImage->imageData, memory->getSharedMemory(), sharedImage.getWidth() * sharedImage.getHeight() * sharedImage.getBytesPerPixel());

        cv::Mat matrix = cv::cvarrToMat(iplImage, true, true, 0);

        result.addFrame(i, featureDetector->detectFeatures(matrix, cv::Mat()));

        cvReleaseImage(&iplImage);
      }
    }

    featureSetDao.save(result);
  }

} // namespace FeatureCreation
