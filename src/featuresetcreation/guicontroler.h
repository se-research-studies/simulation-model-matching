#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

namespace FeatureSetCreation {

    class GuiControler {
    private:
        GuiControler();

    public:
        virtual ~GuiControler();

    public:
        GuiControler(const GuiControler&) = delete;
        GuiControler& operator=(const GuiControler&) = delete;

    public:
        static GuiControler& instance();

    public:
        void setEnabled(bool isEnabled);
        void setImage(const cv::Mat& currentImage, const cv::Mat& mask);
        void setKeyPoints(const std::vector<cv::KeyPoint>& keyPoints);
        void setLines(const std::vector<cv::Vec4i>& lanes);
        void show();

    private:
        bool enabled = true;
        cv::Mat image;
    };

} // namespace FeatureSetCreation

