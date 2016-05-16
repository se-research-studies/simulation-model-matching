#include "featuresetcreator.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include <opendavinci/odtools/player/Player.h>

#include <FeatureSimulation/Common/Utils>
#include <FeatureSimulation/Common/DataManagement/FeatureSetDAO>
#include <FeatureSimulation/FeatureSetCreation/FeatureDetector>
#include <FeatureSimulation/FeatureSetCreation/RecordingPlayer>

namespace FeatureSetCreation {

FeatureSetCreator::FeatureSetCreator(const Settings& settings) {
    recordingFile = settings.recordingFile;
    if (settings.detectionAlg == "ORB") {
        featureDetector.reset(new FeatureDetectorORB(settings));
    } else if (settings.detectionAlg == "ShiTomasi") {
        featureDetector.reset(new FeatureDetectorShiTomasi(settings));
    }
}

FeatureSetCreator::~FeatureSetCreator() {
}

void FeatureSetCreator::createFeatureSet() {
    Common::FeatureSet result(recordingFile);
    int frameNumber = 0;
    RecordingPlayer player(recordingFile);
    cv::Mat mask = createMaskFromRonis(player.imageSize());
    while (player.hasNext()) {
        cv::Mat image = player.next();
        result.addFrame(frameNumber, featureDetector->detectFeatures(image, mask));
        ++frameNumber;
    }
    saveFeatureSet(result);
}

cv::Mat FeatureSetCreator::createMaskFromRonis(const cv::Size& imageSize) const {
    cv::Mat mask;
    std::vector<Common::Region> ronis = loadRonis();
    if (ronis.size() > 0) {
        mask = cv::Mat(imageSize, CV_8U, cv::Scalar(255, 255, 255));
        for (const Common::Region& roni : ronis) {
            std::vector<cv::Point> vertices;
            std::vector<cv::Point> polygon;
            // DO NOT CHANGE THE ORDER! The order of the vertices determines the shape of the polygon
            vertices.push_back(cv::Point(roni.getTopLeft().getX(), roni.getTopLeft().getY()));
            vertices.push_back(cv::Point(roni.getTopRight().getX(), roni.getTopRight().getY()));
            vertices.push_back(cv::Point(roni.getBottomRight().getX(), roni.getBottomRight().getY()));
            vertices.push_back(cv::Point(roni.getBottomLeft().getX(), roni.getBottomLeft().getY()));
            cv::approxPolyDP(vertices, polygon, 1.0, true);
            cv::fillConvexPoly(mask, &polygon[0], polygon.size(), cv::Scalar(0, 0, 0));
        }
    }
    return mask;
}

std::vector<Common::Region> FeatureSetCreator::loadRonis() const {
    try {
        return roniDao.load(recordingFile);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Proceeding without Regions of no Interest." << std::endl;
        return std::vector<Common::Region>();
    }
}


void FeatureSetCreator::saveFeatureSet(const Common::FeatureSet& featureSet) const {
    featureSetDao.beginTransaction();
    featureSetDao.ensureTable();
    featureSetDao.deleteAll(recordingFile);
    featureSetDao.save(featureSet);
    featureSetDao.endTransaction();
}

} // namespace FeatureCreation
