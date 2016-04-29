#include "featuresetcreator.h"

#include <opencv2/core/core.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/imgproc/imgproc.hpp>

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
    odcore::io::URL url("file://" + recordingName);
    odtools::player::Player player(url, false, PLAYER_MEMORYSEGMENT_SIZE, PLAYER_NUMBER_OF_MEMORY_SEGMENTS, false);
    cv::Mat mask = createMaskFromRonis(player);
    Common::FeatureSet result(recordingName);
    for (int i = 0; player.hasMoreData(); ++i) {
      odcore::data::Container container = player.getNextContainerToBeSent();
      if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
        cv::Mat image = readNextImage(container);
        result.addFrame(i, featureDetector->detectFeatures(image, mask));
      }
    }

    featureSetDao.save(result);
  }

  cv::Mat FeatureSetCreator::createMaskFromRonis(odtools::player::Player& player) const {
    cv::Mat mask;
    std::vector<Common::Region> ronis = loadRonis();
    if (ronis.size() > 0) {
      cv::Size imageSize = getImageSize(player);
      mask = cv::Mat(imageSize, CV_8U, cv::Scalar(255, 8, 0));
      for (const Common::Region& roni : ronis) {
        std::vector<cv::Point> vertices;
        std::vector<cv::Point> polygon;
        vertices.push_back(cv::Point(roni.getTopLeft().getX(), roni.getTopLeft().getY()));
        vertices.push_back(cv::Point(roni.getTopRight().getX(), roni.getTopRight().getY()));
        vertices.push_back(cv::Point(roni.getBottomLeft().getX(), roni.getBottomLeft().getY()));
        vertices.push_back(cv::Point(roni.getBottomRight().getX(), roni.getBottomRight().getY()));
        cv::approxPolyDP(vertices, polygon, 1.0, true);
        cv::fillConvexPoly(mask, &polygon[0], polygon.size(), cv::Scalar(0, 0, 0));
      }
    }
    return mask;
  }

  std::vector<Common::Region> FeatureSetCreator::loadRonis() const {
    try {
      return roniDao.load(recordingName);
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
      std::cerr << "Proceeding without Regions of no Interest." << std::endl;
      return std::vector<Common::Region>();
    }
  }

  cv::Size FeatureSetCreator::getImageSize(odtools::player::Player& player) const {
    odcore::data::Container container = player.getNextContainerToBeSent();
    while (container.getDataType() != odcore::data::image::SharedImage::ID()) {
      container = player.getNextContainerToBeSent();
    }
    cv::Mat firstImage = readNextImage(container);
    player.rewind();
    return firstImage.size();
  }

  cv::Mat FeatureSetCreator::readNextImage(odcore::data::Container container) const {
    odcore::data::image::SharedImage sharedImage = container.getData<odcore::data::image::SharedImage>();
    std::shared_ptr<odcore::wrapper::SharedMemory> memory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());
    IplImage* iplImage = cvCreateImage(cvSize(Common::Utils::to<int>(sharedImage.getWidth()), Common::Utils::to<int>(sharedImage.getHeight())), IPL_DEPTH_8U, sharedImage.getBytesPerPixel());
    memcpy(iplImage->imageData, memory->getSharedMemory(), sharedImage.getWidth() * sharedImage.getHeight() * sharedImage.getBytesPerPixel());
    cv::Mat image = cv::cvarrToMat(iplImage, true, true, 0);
    cvReleaseImage(&iplImage);
    return image;
  }

} // namespace FeatureCreation
