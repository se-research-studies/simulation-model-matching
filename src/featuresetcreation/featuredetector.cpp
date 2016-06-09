#include "featuredetector.h"

#include <algorithm>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <FeatureSimulation/Common/utils.h>
#include <FeatureSimulation/Common/Data/feature.h>

namespace FeatureSetCreation {

FeatureDetector::FeatureDetector(const Settings& settings)
    : guiEnabled(settings.guiEnabled), fuzzinessFactor(settings.laneDetectionSettings.fuzzinessFactor), laneDetector(settings.laneDetectionSettings) {
}

FeatureDetector::~FeatureDetector() {
}

Common::DirtyFrame FeatureDetector::detectFeatures(const cv::Mat& image, const cv::Mat& mask) {
    std::vector<cv::KeyPoint> keyPoints = findKeyPoints(image, mask);
    std::vector<cv::Vec4i> lanes = laneDetector.detectLanes(image);
    keyPoints = subtractLanes(keyPoints, lanes);
    if (guiEnabled) {
        showResults(image, mask, keyPoints, lanes);
    }
    return convertToDirtyFrame(keyPoints);
}

std::vector<cv::KeyPoint> FeatureDetector::subtractLanes(const std::vector<cv::KeyPoint>& keyPoints, const std::vector<cv::Vec4i>& lanes) {
    std::vector<cv::KeyPoint> features;
    for (const cv::KeyPoint& keyPoint : keyPoints) {
        bool hitByLane = false;
        const float p1 = keyPoint.pt.x;
        const float p2 = keyPoint.pt.y;
        const float fuzzySize = keyPoint.size * fuzzinessFactor;
        for (const cv::Vec4i& line : lanes) {
            const float v1 = line[0];
            const float v2 = line[1];
            const float w1 = line[2];
            const float w2 = line[3];
            float distance;
            float lineLengthSquared = pointDistanceSquared(v1, v2, w1, w2);
            if (lineLengthSquared == 0.0) { // Line is a point
                distance = pointDistance(p1, p2, v1, v2);
            } else {
                const float scaleFactor = 1.0f / sqrt(lineLengthSquared);
                const float pv1Scaled = (p1 - v1) * scaleFactor;
                const float pv2Scaled = (p2 - v2) * scaleFactor;
                const float vw1Scaled = (w1 - v1) * scaleFactor;
                const float vw2Scaled = (w2 - v2) * scaleFactor;
                const float t = dotProduct(pv1Scaled, pv2Scaled, vw1Scaled, vw2Scaled);
                const float clampedT = std::max(0.0f, std::min(1.0f, t));
                const float projectedX = v1 + clampedT * (w1 - v1);
                const float projectedY = v2 + clampedT * (w2 - v2);
                distance = pointDistance(p1, p2, projectedX, projectedY);
            }

            hitByLane = distance < fuzzySize;
            if (hitByLane) {
                break;
            }
        }
        if (!hitByLane) {
            features.push_back(keyPoint);
        }
    }
    return features;
}

float FeatureDetector::pointDistanceSquared(float a1, float a2, float b1, float b2) const {
    return pow(a1-b1, 2) + pow(a2-b2, 2);
}

float FeatureDetector::pointDistance(float a1, float a2, float b1, float b2) const {
    return sqrt(pointDistanceSquared(a1, a2, b1, b2));
}

float FeatureDetector::dotProduct(float a1, float a2, float b1, float b2) const {
    return a1 * b1 + a2 * b2;
}

void FeatureDetector::showResults(const cv::Mat& image, const cv::Mat& mask, const std::vector<cv::KeyPoint>& keyPoints, const std::vector<cv::Vec4i>& lanes) const {
    cv::Mat completedImage(image.size(), image.type(), cv::Scalar(255, 255, 255));
    image.copyTo(completedImage, mask);
    cv::drawKeypoints(completedImage, keyPoints, completedImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    for (const cv::KeyPoint& keyPoint : keyPoints) {
        cv::circle(completedImage, cv::Point(keyPoint.pt.x, keyPoint.pt.y), keyPoint.size / 2, cv::Scalar(255, 255, 255));
    }
    for (const cv::Vec4i& line : lanes) {
        cv::line(completedImage, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 2, CV_AA);
    }
    cv::imshow("Analyzed Image", completedImage);
    cv::waitKey(/*50*/);
}

Common::DirtyFrame FeatureDetector::convertToDirtyFrame(const std::vector<cv::KeyPoint>& keyPoints) const {
    std::vector<Common::Feature> features;
    for (const cv::KeyPoint& keyPoint : keyPoints) {
        features.push_back(Common::Feature(Common::Utils::to<uint32_t>(keyPoint.pt.x), Common::Utils::to<uint32_t>(keyPoint.pt.y), keyPoint.size));
    }
    return Common::DirtyFrame(move(features));
}

} // namespace FeatureSetCreation
