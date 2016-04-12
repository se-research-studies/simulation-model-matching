#include"Correspondence.h"
#include <boost/archive/binary_oarchive.hpp>
#include <sstream> 

Correspondence::Correspondence()
{
}

Correspondence::Correspondence(RecordedSequence simRecording, list<RecordedSequence> realRecordings)
{
    m_simRecording = simRecording;
    m_realRecordings = realRecordings;
}

RecordedSequence Correspondence::getSimRecording() 
{
    return m_simRecording;
}

void Correspondence::getRealRecordings(list<RecordedSequence>& recordings)
{
    recordings.clear();
    for (RecordedSequence rs : m_realRecordings) 
    {
        recordings.push_back(rs);
    }
}

string Correspondence::toString() 
{
    ostringstream os;
    os << "Correspondence " << "[simRecording=" << m_simRecording.toString();
    os << ", #realRecordings=" << m_realRecordings.size();
    os << ", realRecordings=<";
    string sep = "";
    for (RecordedSequence rs : m_realRecordings) 
    {
        os << sep + rs.toString();
        sep = ", ";
    }
    os << ">]";
    return os.str();
}
