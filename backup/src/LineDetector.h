#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class LineDetector 
{        
    public:
        LineDetector();
        
        void detectLinesHough(const Mat& src, 
                              double rho,
                              double theta, // CV_PI/180
                              int threshold,
                              vector<Vec2f>& lines);
         
        void detectLinesHoughP(const Mat& src, 
                               double rho,
                               double theta, // CV_PI/180
                               int threshold,
                               double srn,
                               double stn,
                               vector<Vec4i>& lines);
                                                   
        void drawLinesHough(const Mat& src, 
                            double rho,
                            double theta, // CV_PI/180
                            int threshold,
                            Mat& dest);
                            
        void drawLinesHoughP(const Mat& src, 
                            double rho,
                            double theta, // CV_PI/180
                            int threshold,
                            double minLineLength,
                            double maxLineGap,
                            Mat& dest);
};

