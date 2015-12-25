#include <stdio.h>
#include <fstream>

#include <opencv2/features2d/features2d.hpp>

#include "../../src/Noise.h"
#include "../../src/RecordedSequence.h"

using namespace std;

int main(int argc, const char* argv[])
{
    // Frame 0 has a single KeyPoint at (1,1) of size 3
    cv::Point2f p(1,1);
    cv::KeyPoint kp(p,3);
    vector<cv::KeyPoint> frame0KeyPoints;
    frame0KeyPoints.push_back(kp);
    
    // Frame 1 has a KeyPoint at (2,4) of size 1 and a KeyPoint at (3,1) 
    // of size 2
    cv::Point2f q(2,4);
    cv::KeyPoint kq(q,1);
    cv::Point2f r(3,1);
    cv::KeyPoint kr(r,2);
    vector<cv::KeyPoint> frame1KeyPoints;
    frame1KeyPoints.push_back(kq);
    frame1KeyPoints.push_back(kr);
    
    // KeyPoints of each frame
    vector<vector<cv::KeyPoint>> keyPointsPerFrame;
    keyPointsPerFrame.push_back(frame0KeyPoints);
    keyPointsPerFrame.push_back(frame1KeyPoints);
    
    RecordedSequence sim("simcrec", 0, 100);
    
    Noise noise(sim, keyPointsPerFrame);

    cout << "----- I/O Part -----" << endl;

    cout << "toString(): " << noise.toString() << endl;
    
    cout << "----- Serialization Part -----" << endl;
    
    // save to file
    {
        ofstream ofs("filename.noise");
        boost::archive::text_oarchive oa(ofs);
    	oa << noise;
        // archive and stream closed when destructors are called
    }
    
    Noise cloned;
    cout << "cloned: " << cloned.toString() << endl;
    
    // load from file
    {
        ifstream ifs("filename.noise");
        boost::archive::text_iarchive ia(ifs);    
    	ia >> cloned; 
        // archive and stream closed when destructors are called
    }
    
    cout << "restored: " << cloned.toString() << endl;
}
