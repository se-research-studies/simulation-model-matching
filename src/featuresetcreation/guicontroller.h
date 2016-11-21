#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

namespace FeatureSetCreation {

    class GuiController {
    private:
        GuiController();

    public:
        virtual ~GuiController();

    public:
        GuiController(const GuiController&) = delete;
        GuiController& operator=(const GuiController&) = delete;

    public:
        static GuiController& getInstance();

    public:
        void setEnabled(bool isEnabled);
        void setImage(const cv::Mat& currentImage, const cv::Mat& mask);
        void setKeyPoints(const std::vector<cv::KeyPoint>& keyPoints);
        void setLines(const std::vector<cv::Vec4i>& lanes);
        void setFrame(uint32_t frame);
        void show();

    private:
        bool enabled = true;
        cv::Mat image;
    };

} // namespace FeatureSetCreation

