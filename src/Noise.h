#ifndef NOISE_H
#define NOISE_H

#include <iostream>
#include <stdio.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;

class Noise 
{        
    private:
        vector<vector<cv::KeyPoint>> m_keyPointsPerFrame;
        
    public:
        Noise();
        Noise(vector<vector<cv::KeyPoint>> keyPointsPerFrame);
        vector<vector<cv::KeyPoint>> getKeyPointsPerFrame();
        vector<cv::KeyPoint> getKeyPointsOfFrame(int frameID);        
        string toString();
        
        friend class boost::serialization::access;
        
        template<class Archive>
        void save(Archive & ar, const unsigned int version) const
        {
            int numFrames = m_keyPointsPerFrame.size();
            ar << numFrames;
            int numFrameKeyPoints = 0;
            for (vector<cv::KeyPoint> frameKPs : m_keyPointsPerFrame) 
            {
                numFrameKeyPoints = frameKPs.size();
                ar << numFrameKeyPoints;
                for (cv::KeyPoint kp : frameKPs)
                {
                    ar << kp.pt.x;
                    ar << kp.pt.y;
                    ar << kp.size;
                }
            }
        }  
        
        template<class Archive>
        void load(Archive & ar, const unsigned int version)
        {
            int numFrames = 0;
            ar >> numFrames;
            int numFrameKeyPoints = 0;
            int kpX, kpY, kpSize;
            
            for (int i=0; i<numFrames; i++) 
            {
                vector<cv::KeyPoint> frameKeyPoints;
                ar >> numFrameKeyPoints;
                for (int j=0; j<numFrameKeyPoints; j++) 
                {
                    ar >> kpX;
                    ar >> kpY;
                    ar >> kpSize;
                    cv::Point2f pt(kpX,kpY);
                    cv::KeyPoint kp(pt,kpSize);
                    frameKeyPoints.push_back(kp);
                }      
                m_keyPointsPerFrame.push_back(frameKeyPoints);
            }
        }

        BOOST_SERIALIZATION_SPLIT_MEMBER()
};

#endif
