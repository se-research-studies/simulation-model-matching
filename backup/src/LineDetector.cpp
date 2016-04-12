#include"LineDetector.h"

LineDetector::LineDetector() 
{
    // cout << "[LineDetector] Default constructor." << endl;
}

void LineDetector::detectLinesHough(const Mat& src, 
                                    double rho,
                                    double theta, // CV_PI/180
                                    int threshold,
                                    vector<Vec2f>& lines)
{
  // cout << "[LineDetector] detectLinesHough()." << endl;
  
  Mat dst;
  Canny(src, dst, 50, 200, 3);
  HoughLines(dst, lines, rho, theta, threshold, 0, 0 );
  // cout << "Lines size: " << lines.size() << endl;
  for( size_t i = 0; i < lines.size(); i++ )
  {
     float rho2 = lines[i][0], theta2 = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta2), b = sin(theta2);
     double x0 = a*rho2, y0 = b*rho2;
     pt1.x = cvRound(x0 + 1000*(-b));
     pt1.y = cvRound(y0 + 1000*(a));
     pt2.x = cvRound(x0 - 1000*(-b));
     pt2.y = cvRound(y0 - 1000*(a));
     // cout << "Found line from (" << pt1.x << "," << pt1.y << ") to (" << pt2.x << "," << pt2.y << ")" << endl;
  }
}

void LineDetector::drawLinesHough(const Mat& src, 
                                  double rho,
                                  double theta, // CV_PI/180
                                  int threshold,
                                  Mat& dest)
{
  // cout << "[LineDetector] drawLinesHough(" << rho << "," << theta << "," << threshold << ")." << endl;
  
  Mat dst;
  Canny(src, dst, 50, 200, 3);
  cvtColor(dst, dest, CV_GRAY2BGR);

  
  vector<Vec2f> lines;
  detectLinesHough(src, rho, theta, threshold, lines);
  for( size_t i = 0; i < lines.size(); i++ )
  {
     float rho2 = lines[i][0], theta2 = lines[i][1];
     Point pt1, pt2;
     double a = cos(theta2), b = sin(theta2);

     double x0 = a*rho2, y0 = b*rho2;
     pt1.x = cvRound(x0 + 1000*(-b));
     pt1.y = cvRound(y0 + 1000*(a));
     pt2.x = cvRound(x0 - 1000*(-b));
     pt2.y = cvRound(y0 - 1000*(a));
     // cout << "Found line from (" << pt1.x << "," << pt1.y << ") to (" << pt2.x << "," << pt2.y << ")";
     line(dest, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
  }
}
 
 
void LineDetector::detectLinesHoughP(const Mat& src, 
                                     double rho,
                                     double theta, // CV_PI/180
                                     int threshold,
                                     double minLineLength,
                                     double maxLineGap,
                                     vector<Vec4i>& lines) 
{
    // cout << "[LineDetector] detectLinesHoughP(" << rho << "," << theta << "," << threshold << "," << minLineLength << "," << maxLineGap << ")." << endl;
  
    Mat dst;
    Canny(src, dst, 50, 200, 3);
    HoughLinesP(dst, lines, rho, theta, threshold, minLineLength, maxLineGap);
}
                    
void LineDetector::drawLinesHoughP(const Mat& src, 
                                   double rho,
                                   double theta, // CV_PI/180
                                   int threshold,
                                   double minLineLength,
                                   double maxLineGap,
                                   Mat& dest)
{
  // cout << "[LineDetector] drawLinesHoughP(" << rho << "," << theta << "," << threshold << "," << minLineLength << "," << maxLineGap << ")." << endl;
  
  Mat dst;
  Canny(src, dst, 50, 200, 3);
  cvtColor(dst, dest, CV_GRAY2BGR);
  
  vector<Vec4i> lines;
  detectLinesHoughP(src, rho, theta, threshold, minLineLength, maxLineGap, lines);

  for(size_t i = 0; i < lines.size(); i++ )
  {
    Vec4i l = lines[i];
    line(dest, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  }
}
