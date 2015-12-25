#ifndef RECORDEDSEQUENCE_H
#define RECORDEDSEQUENCE_H

#include <iostream>
#include <stdio.h>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Noise.h"

using namespace std;

class RecordedSequence 
{        
    private:
        string m_filename;
        int m_startFrame;
        int m_endFrame;
        Noise m_noise;
        
    public:
        RecordedSequence();
        RecordedSequence(string filename, int startFrame, int endFrame);
        string getFilename();
        int getStartFrame();
        int getEndFrame();
        void setNoise(Noise noise);
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_filename;
            ar & m_startFrame;
            ar & m_endFrame;
            ar & m_noise;
        }
        
        string toString();
};

#endif
