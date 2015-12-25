#include"Noise.h"

Noise::Noise()
{
}

Noise::Noise(vector<vector<cv::KeyPoint>> keyPointsPerFrame)
{
    m_keyPointsPerFrame = keyPointsPerFrame;
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
    os << "Noise [#frames=" << m_keyPointsPerFrame.size();
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
