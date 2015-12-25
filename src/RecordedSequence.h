#include <iostream>
#include <stdio.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;

class RecordedSequence 
{        
    private:
        string m_filename;
        int m_startFrame;
        int m_endFrame;
        
    public:
        RecordedSequence(string filename, int startFrame, int endFrame);
        string getFilename();
        int getStartFrame();
        int getEndFrame();
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_filename;
            ar & m_startFrame;
            ar & m_endFrame;
        }
};

