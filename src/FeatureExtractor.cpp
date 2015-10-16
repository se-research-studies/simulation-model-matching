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
  // imshow("source", src);
  
  /*
  Mat dest;
  drawLinesHough(src, 1, CV_PI/180, 200, dest);
  imshow("detected lines", dest);
  */
  
  vector<Vec2f> lines;
  /*
  detectLinesHough(src, 1, CV_PI/180, 200, lines);
  for( size_t i = 0; i < lines.size(); i++ )
  {
     float rho = lines[i][0], theta = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     pt1.x = cvRound(x0 + 1000*(-b));
     pt1.y = cvRound(y0 + 1000*(a));
     pt2.x = cvRound(x0 - 1000*(-b));
     pt2.y = cvRound(y0 - 1000*(a));
     LineIterator it(src, pt1, pt2, 8);
     vector<Vec2f> buf(it.count);
     
     Point p;
     for(int j = 0; j < it.count; j++, ++it)
     {
        p = it.pos();
        cout << "Found hough point at (" << p.x << "," << p.y << ")" << endl;
     } 
  }ength, maxLineGap, lines);

  */

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
  drawFeaturesMinusLines(src, false, subtracted);
  imshow("subtracted", subtracted);
    
  /*
  for (size_t i = 0; i < keyPoints.size(); i++) 
  {
    pt = keyPoints[i].pt;
    cout << "Found feature at (" << pt.x << "," << pt.y << ") of size " << keyPoints[i].size << endl;
    cout << "Rounded to (" << cvRound(pt.x) << "," << cvRound(pt.y) << ")" << endl;
  }
  */
  // waitKey();
}

void FeatureExtractor::subtractLinesFromFeatures(const Mat &src, bool convertToGray, vector<KeyPoint>& residue)
{
    residue.clear();

    // 1. Detect ORB Features
    Mat features;
    vector<KeyPoint> keyPoints;
    getGoodORBFeatures(src, convertToGray, keyPoints);
    
    cout << "[FeatureExtractor] Found " << keyPoints.size() << " key points" << endl;
    
    // 2. Detect Hough lines
    vector<Vec4i> lines;
    detectLinesHoughP(src,1,CV_PI/180,100,50,25,lines);
        
    // 3. Iterate over Hough lines; remove lines pixels from ORB features
    Point p;
    for (size_t i = 0; i < keyPoints.size(); i++)
    {
        Point pt1(lines[0][1],lines[0][1]);
        Point pt2(lines[0][2],lines[0][3]);
        LineIterator it(src, pt1, pt2, 8);
        // cout << "[FeatureExtractor] Checking line from (" << pt1.x << "," << pt1.y << ") to (" << pt2.x << "," << pt2.y << ")" << endl;
        
        // Iterate over each line's pixels
        for(int j = 0; j < it.count; j++, ++it)
        {
            p = it.pos();
            // cout << "Found hough point at (" << p.x << "," << p.y << ")" << endl;
           
            // If the point p is part of a line, and we have detected a 
            // feature on that line, we can remove that feature             
            if (!partOfFeature(p, keyPoints)) 
            {
                residue.push_back(keyPoints[i]); //TODO: Continue here
            }
        } 
    }
    cout << "[FeatureExtractor] Reduced to " << residue.size() << " key points" << endl;
}

void FeatureExtractor::drawFeaturesMinusLines(const Mat &src,
                                              bool convertToGray)
{
  Mat subtracted;
  drawFeaturesMinusLines(src, convertToGray, subtracted);
  imshow("subtracted", subtracted);
}

void FeatureExtractor::drawFeaturesMinusLines(const Mat &src,
                                              bool convertToGray,
                                              Mat &target)
{
    vector<KeyPoint> residue;
    subtractLinesFromFeatures(src, convertToGray, residue);
    drawKeypoints(src, residue, target);
}

bool FeatureExtractor::partOfFeature(Point pt, vector<KeyPoint>& keyPoints) 
{
    Point kp;
    for (size_t i = 0; i < keyPoints.size(); i++) 
    {
        kp = keyPoints[i].pt;
        float r = keyPoints[i].size / 2.0;
        float dX = (kp.x - pt.x) * (kp.x - pt.x);
        float dY = (kp.y - pt.y) * (kp.y - pt.y);
        float r2 = r * r;
        /*
        cout << "dX = " << dX << endl;
        cout << "dY = " << dY << endl;
        cout << "r2 = " << r2 << endl;
        */
        if (dX + dY < r2)
        {
            // cout << "Dropping feature at (" << kp.x << "," << kp.y << ")" << endl;
            return true;
        }
    }
    return false;
}
