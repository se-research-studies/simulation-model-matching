#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// see http://stackoverflow.com/questions/23448420/orb-is-not-detecting-keypoints-in-opencv-2-4-9

class ORBMatcher 
{        
    public:
        ORBMatcher();
        
        /**
         * Calculates the good features of the passed src image using
         * the Shi-Tomasi method and draws markers on the passed target
         * image.
         */
        void drawGoodFeatures(const Mat &src, Mat &target, bool convertToGray);
        
        void getGoodFeatures(const Mat &src, bool convertToGray, vector<KeyPoint>& keyPoints);
};

