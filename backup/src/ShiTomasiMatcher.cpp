#include"ShiTomasiMatcher.h"

// see http://docs.opencv.org/modules/imgproc/doc/feature_detection.html?highlight=goodfeaturestotrack#goodfeaturestotrack
    
ShiTomasiMatcher::ShiTomasiMatcher() 
{
    m_qualityLevel = QUALITY_LEVEL;
    m_minDistance = MIN_DISTANCE;
    m_blockSize = BLOCK_SIZE;
    m_maxCorners = MAX_CORNERS;
    m_useHarrisDetectorInstead = USE_HARRIS;
    m_harrisFreeK = HARRIS_K;
    cout << "[ShiTomasiMatcher] Default constructor." << endl;
    cout << "[ShiTomasiMatcher]   - qualityLevel = " << m_qualityLevel << endl;
    cout << "[ShiTomasiMatcher]   - minDistance  = " << m_minDistance << endl;
    cout << "[ShiTomasiMatcher]   - maxCorners   = " << m_maxCorners << endl;
    cout << "[ShiTomasiMatcher]   - blockSize    = " << m_blockSize << endl;
    cout << "[ShiTomasiMatcher]   - useHarris    = " << m_useHarrisDetectorInstead << endl;
    cout << "[ShiTomasiMatcher]   - harrisK      = " << m_harrisFreeK << endl;
}

ShiTomasiMatcher::ShiTomasiMatcher(double quality, double minDist, int block, int corners, bool useHarris, double freeK) 
{
    m_qualityLevel = quality;
    m_minDistance = minDist;
    m_blockSize = block;
    m_maxCorners = corners;
    m_useHarrisDetectorInstead = useHarris;
    m_harrisFreeK = freeK;
    cout << "[ShiTomasiMatcher] Fancy constructor." << endl;
    cout << "[ShiTomasiMatcher]   - qualityLevel = " << m_qualityLevel << endl;
    cout << "[ShiTomasiMatcher]   - minDistance  = " << m_minDistance << endl;
    cout << "[ShiTomasiMatcher]   - maxCorners   = " << m_maxCorners << endl;
    cout << "[ShiTomasiMatcher]   - blockSize    = " << m_blockSize << endl;
    cout << "[ShiTomasiMatcher]   - useHarris    = " << m_useHarrisDetectorInstead << endl;
    cout << "[ShiTomasiMatcher]   - harrisK      = " << m_harrisFreeK << endl;
}
        
/**
 * Calculates the good features of the passed src image using
 * the Shi-Tomasi method and draws markers on the passed target
 * image.
 */
void ShiTomasiMatcher::drawGoodFeatures(const Mat &src, Mat &target, bool convertToGray) {
  vector<Point2f> corners;
  
  // Convert src to gray-scale image for better results
  Mat src_gray;
  if (convertToGray) 
  {
    cvtColor(src, src_gray, CV_BGR2GRAY);
  }
  else {
    src_gray = src.clone();
  }
  
  goodFeaturesToTrack(src_gray,
                      corners,
                      m_maxCorners,
                      m_qualityLevel,
                      m_minDistance,
                      Mat(), // empty mask 
                      m_blockSize,
                      m_useHarrisDetectorInstead,
                      m_harrisFreeK );
                      
  // imshow("Gray", src_gray);
  // cvWaitKey(1000);

  cout << "[ShiTomasiMatcher] Found " << corners.size() << " corners." << endl;
  // Draw detected corners on target
  int r = 4;
  for(unsigned int i = 0; i < corners.size(); i++ )      
  { 
    circle(target, 
           corners[i], 
           r, 
           Scalar(0,0,204), 
           -1, 
           8, 
           0 ); 
  }          
}

