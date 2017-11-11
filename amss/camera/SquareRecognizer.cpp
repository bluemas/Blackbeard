///////////////////////////////////////////////////////////
//  SquareRecognizer.cpp
//  Implementation of the Class SquareRecognizer
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "SquareRecognizer.h"


SquareRecognizer::SquareRecognizer(){

}

SquareRecognizer::~SquareRecognizer(){

}

bool SquareRecognizer::recognizeSquare(Mat& orgImg, Mat& synthImg) {
    bool found = false;
 #if 0   
    Mat hsv_image;
    Mat lower_blue_hue_range;
    Mat upper_blue_hue_range;
    Mat blue_hue_image;
    Mat bgr_image;
    std::vector<cv::Vec3f> circles;

    
    bgr_image = orgImg.clone();
    
    cv::medianBlur(bgr_image, bgr_image, 3);

    // Convert input image to HSV
    
    cv::cvtColor(bgr_image, hsv_image, cv::COLOR_BGR2HSV);

    // Threshold the HSV image, keep only the blue pixels
    
    cv::inRange(hsv_image, cv::Scalar(0, 150, 100), cv::Scalar(10, 255, 255), lower_blue_hue_range);
    cv::inRange(hsv_image, cv::Scalar(160, 150, 100), cv::Scalar(179, 255, 255), upper_blue_hue_range);

    // Combine the above two images
    
    cv::addWeighted(lower_blue_hue_range, 1.0, upper_blue_hue_range, 1.0, 0.0, blue_hue_image);

    cv::GaussianBlur(blue_hue_image, blue_hue_image, cv::Size(9, 9), 2, 2);

    // Use the Hough transform to detect circles in the combined threshold image
    
    findContours(blue_hue_image, contours, hierarchy, RETR_LIST,CHAIN_APPROX_SIMPLE);// Find the contours of the frame

    // Loop over all detected circles and outline them on the original image

    for(size_t current_circle = 0; current_circle < circles.size(); ++current_circle) {
        cv::Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
        int radius = std::round(circles[current_circle][2]);

        cv::circle(synthImg, center, radius, cv::Scalar(0, 255, 0), 5);
    }    
    
    if (circles.size() > 0)
        found = true;
#endif
    return found;
}