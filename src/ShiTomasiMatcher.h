#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// see http://docs.opencv.org/modules/imgproc/doc/feature_detection.html?highlight=goodfeaturestotrack#goodfeaturestotrack

class ShiTomasiMatcher 
{
    private:
        // Shi-Tomasi configuration
        static const double QUALITY_LEVEL = 0.01;
        static const double MIN_DISTANCE = 5; // Distance between edges
        static const double BLOCK_SIZE = 3;
        static const double MAX_CORNERS = 50; // Maximal # of corners to find
        static const double USE_HARRIS = false;
        static const double HARRIS_K = 0.50; // Harris free parameter 
        
        // Members
        double m_qualityLevel;
        double m_minDistance; // Distance between edges
        int m_blockSize;
        int m_maxCorners; // Maximal # of corners to find
        bool m_useHarrisDetectorInstead;
        double m_harrisFreeK; // Harris free parameter
    public:
        ShiTomasiMatcher();
        ShiTomasiMatcher(double quality, double minDist, int block, int corners, bool useHarris, double freeK);
        
        /**
         * Calculates the good features of the passed src image using
         * the Shi-Tomasi method and draws markers on the passed target
         * image.
         */
        void drawGoodFeatures(const Mat &src, Mat &target, bool convertToGray);
};

