#include "featuresetcreator.h"

#include <iostream>

#include <opencv2/core/core.hpp>

#include <opendavinci/odtools/player/Player.h>

#include <FeatureSimulation/Common/utils.h>
#include <FeatureSimulation/Common/DataManagement/featuresetdao.h>
#include <FeatureSimulation/FeatureSetCreation/featuredetector.h>
#include <FeatureSimulation/FeatureSetCreation/guicontroler.h>
#include <FeatureSimulation/FeatureSetCreation/imagemasker.h>
#include <FeatureSimulation/FeatureSetCreation/recordingplayer.h>

namespace FeatureSetCreation {

    FeatureSetCreator::FeatureSetCreator(const Settings& settings)
        : recordingFile(settings.recordingFile), id(settings.id) {
        if (settings.detectionAlg == "ORB") {
            featureDetector.reset(new FeatureDetectorORB(settings));
        } else if (settings.detectionAlg == "ShiTomasi") {
            featureDetector.reset(new FeatureDetectorShiTomasi(settings));
        }
    }

    FeatureSetCreator::~FeatureSetCreator() {
    }

    // Runs through every image of recordingFile by opening the recording with the RecordingPlayer.
    // Creates a mask from the values set in the .roni file, if present.
    // Then lets the feature detector detect the keypoints in each frame.
    void FeatureSetCreator::createFeatureSet() {
        Common::FeatureSet result(Common::Utils::fileName(recordingFile), id);
        uint32_t frameNumber = 0;
        std::cout << "Loading file " << recordingFile << "..." << std::endl;
        RecordingPlayer player(recordingFile);
        ImageMasker imageMasker(recordingFile);
        cv::Mat mask = imageMasker.createMask(player.imageSize());
        std::cout << "Detecting features..." << std::endl;
        while (player.hasNext()) {
            cv::Mat image = player.next();
            GuiController::instance().setImage(image, mask);
            GuiController::instance().setFrame(frameNumber);
            Common::DirtyFrame dirtyFrame = featureDetector->detectFeatures(image, mask);
            if (dirtyFrame.getFeatureCount() > 0) {
                result.addFrame(frameNumber, featureDetector->detectFeatures(image, mask));
            }
            GuiController::instance().show();
            ++frameNumber;
        }
        std::cout << "Saving results..." << std::endl;
        saveFeatureSet(result);
        std::cout << "Shutting down..." << std::endl;
    }

    void FeatureSetCreator::saveFeatureSet(const Common::FeatureSet& featureSet) const {
        featureSetDao.beginTransaction();
        featureSetDao.ensureTable();
        featureSetDao.deleteAll(featureSet.getRecordingName(), featureSet.getId());
        featureSetDao.save(featureSet);
        featureSetDao.endTransaction();
    }

} // namespace FeatureCreation
