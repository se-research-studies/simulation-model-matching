#include"ORBMatcher.h"

// see http://stackoverflow.com/questions/23448420/orb-is-not-detecting-keypoints-in-opencv-2-4-9
    
ORBMatcher::ORBMatcher() 
{
  // cout << "[ORBMatcher] Default constructor." << endl;
}
        
void ORBMatcher::drawGoodFeatures(const Mat &src, Mat &target, bool convertToGray) 
{
  // cout << "[ORBMatcher] drawGoodFeatures()." << endl;
  
  vector<KeyPoint> keyPoints;
  getGoodFeatures(src,convertToGray,keyPoints);
  drawKeypoints(src, keyPoints, target, Scalar::all(255));
}

void ORBMatcher::getGoodFeatures(const Mat &src, bool convertToGray, vector<KeyPoint>& keyPoints) 
{
  // cout << "[ORBMatcher] getGoodFeatures()." << endl;
  
  // Convert src to gray-scale image for better results
  Mat src_gray;
  if (convertToGray) 
  {
    cvtColor(src, src_gray, CV_BGR2GRAY);
  }
  else {
    src_gray = src.clone();
  }
  
  OrbFeatureDetector detector;
  detector.detect(src_gray, keyPoints);
  // cout << "[ORBMatcher] getGoodFeatures(): Found " << keyPoints.size() << " Keypoints " << endl;
}
