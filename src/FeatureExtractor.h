#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <stdio.h>

#include "LineDetector.h"
#include "Historizer.h"
#include "ORBMatcher.h"

using namespace std;
using namespace cv;

class FeatureExtractor 
{        
    public:
        FeatureExtractor();
        
        void detectLinesHough(const Mat& src, 
                              double rho,
                              double theta,
                              int threshold,
                              vector<Vec2f>& lines);
         
        void detectLinesHoughP(const Mat& src, 
                               double rho,
                               double theta, 
                               int threshold,
                               double srn,
                               double stn,
                               vector<Vec4i>& lines);
                                                   
        void drawLinesHough(const Mat& src, 
                            double rho,
                            double theta, 
                            int threshold,
                            Mat& dest);
                            
        void drawLinesHoughP(const Mat& src, 
                            double rho,
                            double theta, 
                            int threshold,
                            double minLineLength,
                            double maxLineGap,
                            Mat& dest);
       
        void drawRGBHistogram(const Mat &src, 
                              Mat &histogram);
                              
        void drawGoodORBFeatures(const Mat &src, 
                                 Mat &target, 
                                 bool convertToGray);
                              
        void getGoodORBFeatures(const Mat &src, 
                                bool convertToGray, 
                                vector<KeyPoint>& keyPoints);
                                
        /**
         * Shows many feature detection images next to each other
         */
        void showOff(const Mat &src,
                     bool convertToGray);
        
        void subtractLinesFromFeatures(const Mat &src,
                                       bool convertToGray,
                                       set<KeyPoint>& residue);
        
        void drawFeaturesMinusLines(const Mat &src,
                                    bool convertToGray);                    
                                    
        void drawFeaturesMinusLines(const Mat &src,
                                    bool convertToGray,
                                    Mat &target);
    private:
        LineDetector m_detector;
        Historizer m_historizer;
        ORBMatcher m_matcher;
        
        /**
         * Returns true if pt is within the area identified by a keypoint
         */
        bool partOfFeature(Point pt, vector<KeyPoint>& keyPoints);
};
