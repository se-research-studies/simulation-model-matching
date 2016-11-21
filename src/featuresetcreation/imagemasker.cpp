#include "imagemasker.h"

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

namespace FeatureSetCreation {

    ImageMasker::ImageMasker(const std::string recordingFile)
        : recordingFile(recordingFile) {
    }

    ImageMasker::~ImageMasker() {
    }

    cv::Mat ImageMasker::createMask(const cv::Size& imageSize)
    {
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

    std::vector<Common::Region> ImageMasker::loadRonis() const
    {
        try {
            return roniDao.load(recordingFile);
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "Proceeding without Regions of no Interest." << std::endl;
            return std::vector<Common::Region>();
        }
    }

} // namespace FeatureSetCreation
