#include "lanefollower.h"

#include <iostream>

namespace SimulationGame {

    LaneFollower::LaneFollower(int argc, char** argv)
        : AbstractParticipant(argc, argv, "LaneFollower")
    {
    }

    LaneFollower::~LaneFollower()
    {
    }

    void LaneFollower::processImage(const cv::Mat& image)
    {
        static bool useRightLaneMarking = true;
        double e = 0;

        const int32_t CONTROL_SCANLINE = 462; // calibrated length to right: 280px
        const int32_t distance = 280;
        const int32_t width = image.size().width;
        const int32_t height = image.size().height;

//        for (int32_t y = height - 8; y > height * .6; y -= 10) {
//            // Search from middle to the left:
//            cv::Point left;
//            left.y = y;
//            left.x = -1;
//            for(int x = width/2; x < width; x++) {
//                cv::Scalar color = image.at<uchar>(cv::Point(x, y));
//                if (color.val[0] >= 200) {
//                    left.x = x;
//                    break;
//                }
//            }

//            // Search from middle to the right:
//            cv::Point right;
//            right.y = y;
//            right.x = -1;
//            for(int x = width/2; x > 0; x--) {
//                cv::Scalar color = image.at<uchar>(cv::Point(x, y));
//                if (color.val[0] >= 200) {
//                    right.x = x;
//                    break;
//                }
//            }


        IplImage* iplImage;
        iplImage = cvCreateImage(cvSize(image.cols, image.rows), 8, 3);
        IplImage ipltemp = image;
        cvCopy(&ipltemp, iplImage);

        for(int32_t y = height - 8; y > height * .6; y -= 10) {
            // Search from middle to the left:
            CvScalar pixelLeft;
            CvPoint left;
            left.y = y;
            left.x = -1;
            for(int x = width/2; x > 0; x--) {
                pixelLeft = cvGet2D(iplImage, y, x);
                if (pixelLeft.val[0] >= 200) {
                    left.x = x;
                    break;
                }
            }

            // Search from middle to the right:
            CvScalar pixelRight;
            CvPoint right;
            right.y = y;
            right.x = -1;
            for(int x = width/2; x < width; x++) {
                pixelRight = cvGet2D(iplImage, y, x);
                if (pixelRight.val[0] >= 200) {
                    right.x = x;
                    break;
                }
            }

        ////            if (m_debug) {
        ////                if (left.x > 0) {
        ////                    CvScalar green = CV_RGB(0, 255, 0);
        ////                    cvLine(image, cvPoint(width/2, y), left, green, 1, 8);

        ////                    stringstream sstr;
        ////                    sstr << (width/2 - left.x);
        ////                    cvPutText(image, sstr.str().c_str(), cvPoint(width/2 - 100, y - 2), &m_font, green);
        ////                }
        ////                if (right.x > 0) {
        ////                    CvScalar red = CV_RGB(255, 0, 0);
        ////                    cvLine(image, cvPoint(width/2, y), right, red, 1, 8);

        ////                    stringstream sstr;
        ////                    sstr << (right.x - width/2);
        ////                    cvPutText(image, sstr.str().c_str(), cvPoint(width/2 + 100, y - 2), &m_font, red);
        ////                }
        ////            }

            if (y == CONTROL_SCANLINE) {
                // Calculate the deviation error.
                if (right.x > 0) {
                    if (!useRightLaneMarking) {
                        m_eSum = 0;
                        m_eOld = 0;
                    }

                    e = ((right.x - width/2.0) - distance)/distance;

                    useRightLaneMarking = true;
                }
                else if (left.x > 0) {
                    if (useRightLaneMarking) {
                        m_eSum = 0;
                        m_eOld = 0;
                    }

                    e = (distance - (width/2.0 - left.x))/distance;

                    useRightLaneMarking = false;
                }
                else {
                    // If no measurements are available, reset PID controller.
                    m_eSum = 0;
                    m_eOld = 0;
                }
            }
        }

        odcore::data::TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);
        m_previousTime = currentTime;

        if (fabs(e) < 1e-2) {
            m_eSum = 0;
        }
        else {
            m_eSum += e;
        }
//            const double Kp = 2.5;
//            const double Ki = 8.5;
//            const double Kd = 0;

        // The following values have been determined by Twiddle algorithm.
        const double Kp = 0.4482626884328734;
        const double Ki = 3.103197570937628;
        const double Kd = 0.030450210485408566;

        const double p = Kp * e;
        const double i = Ki * timeStep * m_eSum;
        const double d = Kd * (e - m_eOld)/timeStep;
        m_eOld = e;

        const double y = p + i + d;
        double desiredSteering = 0;
        if (fabs(e) > 1e-2) {
            desiredSteering = y;

            if (desiredSteering > 25.0) {
                desiredSteering = 25.0;
            }
            if (desiredSteering < -25.0) {
                desiredSteering = -25.0;
            }
        }
        std::cerr << "PID: " << "e = " << e << ", eSum = " << m_eSum << ", desiredSteering = " << desiredSteering << ", y = " << y << std::endl;


        setControls(2, desiredSteering);
    }


} // namespace SimulationGame
