#include"RecordedSequence.h"
#include <boost/archive/binary_oarchive.hpp>

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
