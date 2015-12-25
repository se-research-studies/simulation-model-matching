#include"Noise.h"

Noise::Noise()
{
}

Noise::Noise(RecordedSequence source, vector<vector<cv::KeyPoint>> keyPointsPerFrame)
{
    m_source = source;
    m_keyPointsPerFrame = keyPointsPerFrame;
}

RecordedSequence Noise::getSource()
{
    return m_source;
}

vector<vector<cv::KeyPoint>> Noise::getKeyPointsPerFrame()
{
    return m_keyPointsPerFrame;
}

vector<cv::KeyPoint> Noise::getKeyPointsOfFrame(int frameID)
{
    return m_keyPointsPerFrame[frameID];
}        

string Noise::toString()
{
    ostringstream os;
    os << "Noise [source=" << m_source.toString() << ", #frames=" << m_keyPointsPerFrame.size();
    os << ", keyPointsPerFrame=<" ;
    int frameID = 0;
    for (vector<cv::KeyPoint> frameKPs : m_keyPointsPerFrame) 
    {
        os << "frame" << frameID++ << ":";
        for (cv::KeyPoint kp : frameKPs)
        {
            os << "(" << kp.pt.x << "," << kp.pt.y << "," << kp.size << ") ";
        }
    }
    os << ">]";
    return os.str();
}
