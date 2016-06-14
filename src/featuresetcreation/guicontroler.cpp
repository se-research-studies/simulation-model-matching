#include "guicontroler.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace FeatureSetCreation {

    GuiControler::GuiControler() {
    }

    GuiControler::~GuiControler() {
    }

    GuiControler& GuiControler::instance()
    {
        static GuiControler instance;
        return instance;
    }

    void GuiControler::setEnabled(bool isEnabled)
    {
        enabled = isEnabled;
    }

    void GuiControler::setImage(const cv::Mat& currentImage, const cv::Mat& mask)
    {
        image = cv::Mat(currentImage.size(), currentImage.type(), cv::Scalar(255, 255, 255));
        currentImage.copyTo(image, mask);
    }

    void GuiControler::setKeyPoints(const std::vector<cv::KeyPoint>& keyPoints)
    {
        cv::drawKeypoints(image, keyPoints, image, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    }

    void GuiControler::setLines(const std::vector<cv::Vec4i>& lanes)
    {
        for (const cv::Vec4i& line : lanes) {
            cv::line(image, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 2, CV_AA);
        }
    }

    void GuiControler::show()
    {
        if (enabled) {
            cv::imshow("Analyzed Image", image);
            cv::waitKey(/*50*/);
        }
    }

} // namespace FeatureSetCreation
