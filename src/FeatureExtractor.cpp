#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor() 
{
    // cout << "[FeatureExtractor] Default constructor." << endl;
}

void FeatureExtractor::detectLinesHough(const Mat& src, 
                                    double rho,
                                    double theta, // CV_PI/180
                                    int threshold,
                                    vector<Vec2f>& lines)
{
  // cout << "[FeatureExtractor] detectLinesHough()." << endl;
  m_detector.detectLinesHough(src,rho,theta,threshold,lines);
}

void FeatureExtractor::drawLinesHough(const Mat& src, 
                                  double rho,
                                  double theta, // CV_PI/180
                                  int threshold,
                                  Mat& dest)
{
  // cout << "[FeatureExtractor] drawLinesHough()." << endl;
  m_detector.drawLinesHough(src,rho,theta,threshold,dest);
}
 
 
void FeatureExtractor::detectLinesHoughP(const Mat& src, 
                                     double rho,
                                     double theta, // CV_PI/180
                                     int threshold,
                                     double minLineLength,
                                     double maxLineGap,
                                     vector<Vec4i>& lines) 
{
  // cout << "[FeatureExtractor] detectLinesHoughP()." << endl;
  m_detector.detectLinesHoughP(src,rho,theta,threshold,minLineLength,maxLineGap,lines);
}
                    
void FeatureExtractor::drawLinesHoughP(const Mat& src, 
                                   double rho,
                                   double theta, // CV_PI/180
                                   int threshold,
                                   double minLineLength,
                                   double maxLineGap,
                                   Mat& dest)
{
  // cout << "[FeatureExtractor] drawLinesHoughP()." << endl;
  m_detector.drawLinesHoughP(src,rho,theta,threshold,minLineLength,maxLineGap,dest);
}

void FeatureExtractor::drawRGBHistogram(const Mat &src, Mat &dest)
{
  // cout << "[FeatureExtractor] drawRGBHistogram()." << endl;
  m_historizer.drawRGBHistogram(src,dest);
}

void FeatureExtractor::drawGoodORBFeatures(const Mat &src, Mat &target, bool convertToGray) 
{
  m_matcher.drawGoodFeatures(src,target,convertToGray);
}

void FeatureExtractor::getGoodORBFeatures(const Mat &src, bool convertToGray, vector<KeyPoint>& keyPoints) 
{
  m_matcher.getGoodFeatures(src, convertToGray, keyPoints);
}

void FeatureExtractor::showOff(const Mat &src, bool convertToGray) 
{
  vector<Vec2f> lines;

  Mat destP;
  drawLinesHoughP(src, 1, CV_PI/180, 100, 50, 30, destP);
  imshow("detected pLines", destP);
  
  Mat histogram;
  drawRGBHistogram(src, histogram);
  imshow("histogram", histogram);
  
  Mat features;
  vector<KeyPoint> keyPoints;
  Point2f pt;
  getGoodORBFeatures(src, convertToGray, keyPoints); //TODO: List of feature key points
  drawGoodORBFeatures(src, features, convertToGray);
  imshow("features", features);
  
  Mat subtracted;
  drawFeaturesMinusLines(src, false, 0, subtracted);
  imshow("subtracted", subtracted);
    
}

/**
 * Calculates the ORB features of the passed image, its Hough lines and 
 * removes all points in an epsilon environment on lines from the features 
 * (they are interpreted as  lanes). Returns the remaining features.
 * 
 * @param: src, the image to process
 * @param: convertToGray, includes gray-scale conversion for colored images
 * @param: epsilon, lane-environment where features should be removed
 * @param: residue, remaining features after subtraction
 */ 
void FeatureExtractor::subtractLinesFromFeaturesSmart(const Mat &src, bool convertToGray, float epsilon, vector<KeyPoint>& residue)
{
    // vector<int> savedKeyPointIndices;
    residue.clear();

    // 1. Detect ORB Features
    Mat features;
    vector<KeyPoint> keyPoints;
    getGoodORBFeatures(src, convertToGray, keyPoints);
    
    cout << "[FeatureExtractor] Found " << keyPoints.size() << " key points (e=" << epsilon << ")" << endl;
    
    // 2. Detect Hough lines
    vector<Vec4i> lines;
    detectLinesHoughP(src,1,CV_PI/180,100,50,25,lines);
    
    // Point *from, *to, pt;
    Rect *rect;
    KeyPoint kp;
    
    unsigned int n = lines.size();
    
    float x0, y0, x1, y1;
    
    vector<Rect> rects(n);
    for (size_t i = 0; i < n; i++) 
    {
        x0 = lines[i][0] - epsilon;
        y0 = lines[i][1];
        x1 = lines[i][2] + epsilon;
        y1 = lines[i][3];
        // cout << "[XXX] Rect from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")" << endl;
        rect = new Rect(
            Point(x0, y0),
            Point(x1, y1)
            );
        rects.push_back(*rect);
    }
      
    for (size_t i = 0; i < keyPoints.size(); i++)
    {
        kp = keyPoints[i]; 
        bool found = false;  
        for (size_t j = 0; j < n; j++) 
        {
            if (rects[j].contains(kp.pt))
            {
            cout << "[XXX] comparing keypoint at (" << kp.pt.x << "," << kp.pt.y << " with line from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ")" << endl;
                found = true;
                break;
            }
        }
        if (!found) 
        {
          residue.push_back(kp);
        }
    }
    cout << "[FeatureExtractor] Reduced to " << residue.size() << " key points" << endl;
}

/**
 * Calculates the ORB features of the passed image, its Hough lines and 
 * removes all points in an epsilon environment on lines from the features 
 * (they are interpreted as  lanes). Returns the remaining features.
 * 
 * @param: src, the image to process
 * @param: convertToGray, includes gray-scale conversion for colored images
 * @param: epsilon, lane-environment where features should be removed
 * @param: residue, remaining features after subtraction
 */ 
void FeatureExtractor::subtractLinesFromFeatures(const Mat &src, bool convertToGray, float epsilon, vector<KeyPoint>& residue)
{
    // vector<int> savedKeyPointIndices;
    residue.clear();

    // 1. Detect ORB Features
    Mat features;
    vector<KeyPoint> keyPoints;
    getGoodORBFeatures(src, convertToGray, keyPoints);
    
    // 2. Detect Hough lines
    vector<Vec4i> lines;
    detectLinesHoughP(src,1,CV_PI/180,100,50,25,lines);
        
    // 3. Iterate over features (to check for each feature whether it is on
    // a Hough line
    KeyPoint kp;
    for (size_t i = 0; i < keyPoints.size(); i++)
    {
      kp = keyPoints[i];
      // If the KeyPoint is not on any line, we save it
      if (!isKeyPointOnLine(src, kp, epsilon, lines))
      {
        residue.push_back(kp);
      }
    }
    cout << "[FeatureExtractor] Reduced from " << keyPoints.size() << " to " << residue.size() << " key points with e = " << epsilon << endl;
}

/**
 * Checks whether the passed KeyPoint kp is on one of the passed lines.
 *
 * @param src, source image 
 * @param kp, KeyPoint to investigate
 * @param epsilon, currently unused
 * @param lines, the lines to investigate
 * @return true, iff any point of the passed lines is in the environment of the KeyPoint
 */
bool FeatureExtractor::isKeyPointOnLine(const Mat &src, const KeyPoint kp, const float epsilon, const vector<Vec4i> lines) 
{
  Point *from, *to, pt;
  for (size_t i = 0; i < lines.size(); i++)
  {
    from = new Point(lines[i][1],lines[i][1]);
    to = new Point(lines[i][2],lines[i][3]);
    LineIterator it(src, *from, *to, 8);
    for(int j = 0; j < it.count; j++, ++it)
    {
      pt = it.pos();
      if (keyPointContains(kp, pt, epsilon))
      {
        // cout << "[FeatureExtractor] KeyPoint" << kp.pt << " is on line (" << from->x << "," << from->y << ") to (" << to->x << "," << to->y << ") with e = " << epsilon << endl;
        return true;
      }
    }
  }
  return false;
}

/**
 * Checks whether the passed Point pt is in the passed KeyPoint's environment
 *
 * @param kp, KeyPoint to investigate
 * @param pt, Point to investigate
 * @return true, iff pt is in the environment of the KeyPoint
 */
bool FeatureExtractor::keyPointContains(const KeyPoint kp, 
                                        const Point pt,
                                        const float epsilon) 
{
  float r = kp.size / 2.0;
  // float dX = (kp.pt.x - pt.x) * (kp.pt.x - pt.x);
  // float dY = (kp.pt.y - pt.y) * (kp.pt.y - pt.y);
  
  float dX = abs(kp.pt.x - pt.x);
  float dY = abs(kp.pt.y - pt.y);
  // float r2 = r * r;
  if (dX <=r && dY <= r && epsilon >= 0)
  {
    return true;
  }
  return false;
}

void FeatureExtractor::drawFeaturesMinusLines(const Mat &src,
                                              const bool convertToGray,
                                              const float epsilon)
{
  Mat subtracted;
  drawFeaturesMinusLines(src, convertToGray, epsilon, subtracted);
  imshow("subtracted", subtracted);
}

void FeatureExtractor::drawFeaturesMinusLines(const Mat &src,
                                              const bool convertToGray,
                                              const float epsilon,
                                              Mat &target)
{
    vector<KeyPoint> residue;
    subtractLinesFromFeatures(src, convertToGray, epsilon, residue);
    //TODO: subtractCarFromFeatures(src, convertToGray, residue);
    drawKeypoints(src, residue, target);
}
