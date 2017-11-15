///////////////////////////////////////////////////////////
//  SquareRecognizer.cpp
//  Implementation of the Class SquareRecognizer
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "SquareRecognizer.h"

using namespace std;
static const cv::Scalar END_SQUARE_DETECT_COLOR(0.0, 0.0, 0.0);

SquareRecognizer::SquareRecognizer(){

}

SquareRecognizer::~SquareRecognizer(){

}

bool SquareRecognizer::recognizeSquare(Mat& orgImg, Mat& synthImg) {
    bool found = false; 
    Mat hsv_image;
    Mat lower_blue_hue_range;
    Mat upper_blue_hue_range;
    Mat blue_hue_image;
    Mat bgr_image;
   vector<vector<Point>> contours;
   vector<Vec4i> hierarchy;

    bgr_image = orgImg.clone();
    
    cv::medianBlur(bgr_image, bgr_image, 3);

    // Convert input image to HSV
    
    cv::cvtColor(bgr_image, hsv_image, cv::COLOR_BGR2HSV);

    // Threshold the HSV image, keep only the blue pixels
    
    cv::inRange(hsv_image, cv::Scalar(0, 0, 70), cv::Scalar(40, 45, 180), lower_blue_hue_range);
    cv::inRange(hsv_image, cv::Scalar(90, 10, 70), cv::Scalar(180, 100, 180), upper_blue_hue_range);

    // Combine the above two images
    
    cv::addWeighted(lower_blue_hue_range, 1.0, upper_blue_hue_range, 1.0, 0.0, blue_hue_image);

    cv::GaussianBlur(blue_hue_image, blue_hue_image, cv::Size(9, 9), 2, 2);

    // Use the Hough transform to detect circles in the combined threshold image
    
    findContours(blue_hue_image, contours, hierarchy, RETR_LIST,CHAIN_APPROX_SIMPLE);// Find the contours of the frame

    // Loop over all detected circles and outline them on the original image
    float totalArea = 0.0;
    for(unsigned int i = 0; i<contours.size();i++)  {
         Moments mu = moments(contours[i]);
       if (mu.m00 > 7000.0) // area threadhold
        {
           Rect r = boundingRect(contours[i]);
           rectangle(synthImg, r, END_SQUARE_DETECT_COLOR,3); // Draw contours found 
           totalArea += mu.m00;
         }       

    } 
    if (totalArea > 45000.0) {
        printf("EndSquare found, recognized EndSquare area is %f\n", totalArea);
        found = true;
    }

    return found;
}