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
        // Code from LaneFollower.cpp:

//        static bool useRightLaneMarking = true;
//                    double e = 0;

//                    const int32_t CONTROL_SCANLINE = 462; // calibrated length to right: 280px
//                    const int32_t distance = 280;

//                    TimeStamp beforeImageProcessing;
//                    for(int32_t y = m_image->height - 8; y > m_image->height * .6; y -= 10) {
//                        // Search from middle to the left:
//                        CvScalar pixelLeft;
//                        CvPoint left;
//                        left.y = y;
//                        left.x = -1;
//                        for(int x = m_image->width/2; x > 0; x--) {
//                            pixelLeft = cvGet2D(m_image, y, x);
//                            if (pixelLeft.val[0] >= 200) {
//                                left.x = x;
//                                break;
//                            }
//                        }

//                        // Search from middle to the right:
//                        CvScalar pixelRight;
//                        CvPoint right;
//                        right.y = y;
//                        right.x = -1;
//                        for(int x = m_image->width/2; x < m_image->width; x++) {
//                            pixelRight = cvGet2D(m_image, y, x);
//                            if (pixelRight.val[0] >= 200) {
//                                right.x = x;
//                                break;
//                            }
//                        }

//                        if (m_debug) {
//                            if (left.x > 0) {
//                                CvScalar green = CV_RGB(0, 255, 0);
//                                cvLine(m_image, cvPoint(m_image->width/2, y), left, green, 1, 8);

//                                stringstream sstr;
//                                sstr << (m_image->width/2 - left.x);
//                                cvPutText(m_image, sstr.str().c_str(), cvPoint(m_image->width/2 - 100, y - 2), &m_font, green);
//                            }
//                            if (right.x > 0) {
//                                CvScalar red = CV_RGB(255, 0, 0);
//                                cvLine(m_image, cvPoint(m_image->width/2, y), right, red, 1, 8);

//                                stringstream sstr;
//                                sstr << (right.x - m_image->width/2);
//                                cvPutText(m_image, sstr.str().c_str(), cvPoint(m_image->width/2 + 100, y - 2), &m_font, red);
//                            }
//                        }

//                        if (y == CONTROL_SCANLINE) {
//                            // Calculate the deviation error.
//                            if (right.x > 0) {
//                                if (!useRightLaneMarking) {
//                                    m_eSum = 0;
//                                    m_eOld = 0;
//                                }

//                                e = ((right.x - m_image->width/2.0) - distance)/distance;

//                                useRightLaneMarking = true;
//                            }
//                            else if (left.x > 0) {
//                                if (useRightLaneMarking) {
//                                    m_eSum = 0;
//                                    m_eOld = 0;
//                                }

//                                e = (distance - (m_image->width/2.0 - left.x))/distance;

//                                useRightLaneMarking = false;
//                            }
//                            else {
//                                // If no measurements are available, reset PID controller.
//                                m_eSum = 0;
//                                m_eOld = 0;
//                            }
//                        }
//                    }

//                    TimeStamp afterImageProcessing;
//                    cerr << "Processing time: " << (afterImageProcessing.toMicroseconds() - beforeImageProcessing.toMicroseconds())/1000.0 << "ms." << endl;

//                    // Show resulting features.
//                    if (m_debug) {
//                        if (m_image != NULL) {
//                            cvShowImage("WindowShowImage", m_image);
//                            cvWaitKey(10);
//                        }
//                    }

//                    TimeStamp currentTime;
//                    double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);
//                    m_previousTime = currentTime;

//                    if (fabs(e) < 1e-2) {
//                        m_eSum = 0;
//                    }
//                    else {
//                        m_eSum += e;
//                    }
//        //            const double Kp = 2.5;
//        //            const double Ki = 8.5;
//        //            const double Kd = 0;

//                    // The following values have been determined by Twiddle algorithm.
//                    const double Kp = 0.4482626884328734;
//                    const double Ki = 3.103197570937628;
//                    const double Kd = 0.030450210485408566;

//                    const double p = Kp * e;
//                    const double i = Ki * timeStep * m_eSum;
//                    const double d = Kd * (e - m_eOld)/timeStep;
//                    m_eOld = e;

//                    const double y = p + i + d;
//                    double desiredSteering = 0;
//                    if (fabs(e) > 1e-2) {
//                        desiredSteering = y;

//                        if (desiredSteering > 25.0) {
//                            desiredSteering = 25.0;
//                        }
//                        if (desiredSteering < -25.0) {
//                            desiredSteering = -25.0;
//                        }
//                    }
//                    cerr << "PID: " << "e = " << e << ", eSum = " << m_eSum << ", desiredSteering = " << desiredSteering << ", y = " << y << endl;


//                    // Go forward.
//                    m_vehicleControl.setSpeed(2);
//                    m_vehicleControl.setSteeringWheelAngle(desiredSteering);
    }


} // namespace SimulationGame
