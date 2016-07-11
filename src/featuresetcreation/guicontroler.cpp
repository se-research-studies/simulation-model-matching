#include "guicontroller.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace FeatureSetCreation {

    GuiController::GuiController() {
    }

    GuiController::~GuiController() {
    }

    GuiController& GuiController::instance()
    {
        static GuiController instance;
        return instance;
    }

    void GuiController::setEnabled(bool isEnabled)
    {
        enabled = isEnabled;
    }

    void GuiController::setImage(const cv::Mat& currentImage, const cv::Mat& mask)
    {
        image = cv::Mat(currentImage.size(), currentImage.type(), cv::Scalar(255, 255, 255));
        currentImage.copyTo(image, mask);
    }

    void GuiController::setKeyPoints(const std::vector<cv::KeyPoint>& keyPoints)
    {
        cv::drawKeypoints(image, keyPoints, image, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    }

    void GuiController::setLines(const std::vector<cv::Vec4i>& lanes)
    {
        for (const cv::Vec4i& line : lanes) {
            cv::line(image, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 2, CV_AA);
        }
    }

    void GuiController::setFrame(uint32_t frame)
    {
        cv::putText(image, std::to_string(frame), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,255,255), 2);
    }

    void GuiController::show()
    {
        if (enabled) {
            cv::imshow("Analyzed Image", image);
            cv::waitKey(10);
        }
    }

} // namespace FeatureSetCreation
