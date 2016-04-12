#ifndef CORRESPONDENCE_H
#define CORRESPONDENCE_H

#include <iostream>
#include <stdio.h>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>

#include "RecordedSequence.h"

using namespace std;

class Correspondence 
{        
    private:
        RecordedSequence m_simRecording;
        list<RecordedSequence> m_realRecordings;
        
    public:
        Correspondence();
        Correspondence(RecordedSequence simRecording, list<RecordedSequence> realRecordings);
        RecordedSequence getSimRecording();
        void getRealRecordings(list<RecordedSequence>& recordings);  
        string toString();    
        
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            // Supposedly, boost isn't compiled with -Weffc++ 
            // Thus we need to do something with version.
            if (version > -1) 
            {
                ar & m_simRecording;
                ar & m_realRecordings;
            }
        }  
};

#endif
