#ifndef NOISE_H
#define NOISE_H

#include <iostream>
#include <stdio.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "RecordedSequence.h"

using namespace std;

class Noise 
{        
    private:
        RecordedSequence m_source;
        vector<vector<cv::KeyPoint>> m_keyPointsPerFrame;
        
    public:
        Noise();
        Noise(RecordedSequence source, vector<vector<cv::KeyPoint>> keyPointsPerFrame);
        RecordedSequence getSource();
        vector<vector<cv::KeyPoint>> getKeyPointsPerFrame();
        vector<cv::KeyPoint> getKeyPointsOfFrame(int frameID);        
        string toString();
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_source;
            for (vector<cv::KeyPoint> frameKPs : m_keyPointsPerFrame) 
            {
                for (cv::KeyPoint kp : frameKPs)
                {
                    ar & kp.pt.x;
                    ar & kp.pt.y;
                    ar & kp.size;
                }
            }
        }  
};

#endif
