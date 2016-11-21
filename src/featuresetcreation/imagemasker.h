#pragma once

#include <opencv2/core/core.hpp>

#include <FeatureSimulation/Common/DataManagement/ronidao.h>

namespace FeatureSetCreation {

    class ImageMasker {
    public:
        ImageMasker(const std::string recordingFile);
        virtual ~ImageMasker();

    public:
        cv::Mat createMask(const cv::Size& imageSize);

    private:
        std::vector<Common::Region> loadRonis() const;

    private:
        const std::string recordingFile;
        Common::RoniDAO roniDao;
    };

} // namespace FeatureSetCreation

