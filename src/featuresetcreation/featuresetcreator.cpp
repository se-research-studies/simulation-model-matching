#include "featuresetcreator.h"

#include <opencv2/core/core.hpp>

#include <opendavinci/odtools/player/Player.h>

#include <FeatureSimulation/Common/utils.h>
#include <FeatureSimulation/Common/DataManagement/featuresetdao.h>
#include <FeatureSimulation/FeatureSetCreation/featuredetector.h>
#include <FeatureSimulation/FeatureSetCreation/guicontroler.h>
#include <FeatureSimulation/FeatureSetCreation/imagemasker.h>
#include <FeatureSimulation/FeatureSetCreation/recordingplayer.h>

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
        Common::FeatureSet result(Common::Utils::fileName(recordingFile));
        uint32_t frameNumber = 0;
        std::cout << "Loading file " << recordingFile << "..." << std::endl;
        RecordingPlayer player(recordingFile);
        ImageMasker imageMasker(recordingFile);
        cv::Mat mask = imageMasker.createMask(player.imageSize());
        std::cout << "Detecting features..." << std::endl;
        while (player.hasNext()) {
            cv::Mat image = player.next();
            GuiControler::instance().setImage(image, mask);
            Common::DirtyFrame dirtyFrame = featureDetector->detectFeatures(image, mask);
            if (dirtyFrame.getFeatureCount() > 0) {
                result.addFrame(frameNumber, featureDetector->detectFeatures(image, mask));
            }
            GuiControler::instance().show();
            ++frameNumber;
        }
        std::cout << "Saving results..." << std::endl;
        saveFeatureSet(result);
        std::cout << "Shutting down..." << std::endl;
    }

    void FeatureSetCreator::saveFeatureSet(const Common::FeatureSet& featureSet) const {
        featureSetDao.beginTransaction();
        featureSetDao.ensureTable();
        featureSetDao.deleteAll(recordingFile);
        featureSetDao.save(featureSet);
        featureSetDao.endTransaction();
    }

} // namespace FeatureCreation
