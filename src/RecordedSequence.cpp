#include"RecordedSequence.h"
#include <boost/archive/binary_oarchive.hpp>
#include <sstream> 

#include "Noise.h"

RecordedSequence::RecordedSequence()
{
    // -Weffc++ warnings on member initialization are erroneous
    // http://stackoverflow.com/questions/14002454/can-i-ignore-the-gcc-warning-foom-bar-should-be-initialized-in-the-member-i
    m_filename = "NULL";
    m_startFrame = -1;
    m_endFrame = -1;
    m_noise = Noise();
}

RecordedSequence::RecordedSequence(string filename, int startFrame, int endFrame) 
{
    m_filename = filename;
    m_startFrame = startFrame;
    m_endFrame = endFrame;
}
        
string RecordedSequence::getFilename() 
{
  return m_filename;
}

int RecordedSequence::getStartFrame() 
{
  return m_startFrame;
}

int RecordedSequence::getEndFrame() 
{
  return m_endFrame;
}

void RecordedSequence::setNoise(Noise noise)
{
    m_noise = noise;
}

string RecordedSequence::toString() 
{
    ostringstream os;
    os << "RecordedSequence [filename=" << m_filename;
    os << ", startFrame=" << m_startFrame;
    os << ", endFrame=" << m_startFrame;
    os << ", noise=" << m_noise.toString() << "]";
    return os.str();
}
