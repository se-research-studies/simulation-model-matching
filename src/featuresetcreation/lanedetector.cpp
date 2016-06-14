#include "lanedetector.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/FeatureSetCreation/guicontroler.h>

namespace FeatureSetCreation {

    LaneDetector::LaneDetector(const LaneDetectionSettings& settings)
        : settings(settings) {
    }

    LaneDetector::~LaneDetector() {
    }

    std::vector<cv::KeyPoint> LaneDetector::subtractLanes(const cv::Mat& image, const std::vector<cv::KeyPoint>& keyPoints)
    {
        std::vector<cv::Vec4i> lines = detectLines(image);
        std::vector<cv::KeyPoint> features;
        for (const cv::KeyPoint& keyPoint : keyPoints) {
            bool hitByLine = false;
            for (const cv::Vec4i& line : lines) {
                hitByLine = getsHitByLine(keyPoint.pt, line);
                if (hitByLine) {
                    break;
                }
            }
            if (!hitByLine) {
                features.push_back(keyPoint);
            }
        }
        return features;
    }

    std::vector<cv::Vec4i> LaneDetector::detectLines(const cv::Mat& image) {
        cv::Mat cannyImage;
        cv::Canny(image, cannyImage, settings.firstThreshold, settings.secondThreshold, settings.apertureSize);
        std::vector<cv::Vec4i> lines;
        cv::HoughLinesP(cannyImage, lines, settings.rho, settings.theta, settings.voteThreshold, settings.minLineLength, settings.maxLineGap);
        GuiControler::instance().setLines(lines);
        return lines;
    }

    bool LaneDetector::getsHitByLine(const cv::Point2f& point, const cv::Vec4i& line) const
    {
        const cv::Point2f lineStart(line[0], line[1]);
        const cv::Point2f lineEnd(line[2], line[3]);
        float lineLengthSquared = pointDistanceSquared(lineStart, lineEnd);
        float distance;
        if (lineLengthSquared == 0.0) { // Line is a point
            distance = pointDistance(point, lineStart);
        } else {
            cv::Point2f projectedPoint = projectPointOntoLine(point, lineLengthSquared, lineStart, lineEnd);
            distance = pointDistance(point, projectedPoint);
        }
        return distance <= settings.maxDistance;
    }

    float LaneDetector::pointDistanceSquared(const cv::Point2f& a, const cv::Point2f& b) const
    {
        return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
    }

    float LaneDetector::pointDistance(const cv::Point2f& a, const cv::Point2f& b) const
    {
        return sqrt(pointDistanceSquared(a, b));
    }

    cv::Point2f LaneDetector::projectPointOntoLine(const cv::Point2f& p, const float lineLengthSquared, const cv::Point2f& lineStart, const cv::Point2f& lineEnd) const
    {
        const float lineLength = sqrt(lineLengthSquared);
        const float pointToLineXScaled = (p.x - lineStart.x) / lineLength;
        const float pointToLineYScaled = (p.y - lineStart.y) / lineLength;
        const float lineX = lineEnd.x - lineStart.x;
        const float lineY = lineEnd.y - lineStart.y;
        const float lineXScaled = lineX / lineLength;
        const float lineYScaled = lineY / lineLength;
        const float t = pointToLineXScaled * lineXScaled + pointToLineYScaled * lineYScaled;
        const float clampedT = std::max(0.0f, std::min(1.0f, t));
        const float projectedX = lineStart.x + clampedT * lineX;
        const float projectedY = lineStart.y + clampedT * lineY;
        return cv::Point2f(projectedX, projectedY);
    }

} // namespace FeatureSetCreation
