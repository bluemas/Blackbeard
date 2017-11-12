///////////////////////////////////////////////////////////
//  CameraReader.cpp
//  Implementation of the Class CameraReader
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "CameraReader.h"

#define WIDTH  320
#define HEIGHT 240
#define FPS 30

using namespace cv;

CameraReader::CameraReader() {
    mCapture =cvCreateCameraCapture(0);   // Open default Camera
    if(!mCapture) {
         printf("Camera Not Initialized\n");
    }
    if (cvSetCaptureProperty(mCapture, CV_CAP_PROP_FRAME_WIDTH,WIDTH) == 0) { //Set Camera width
        printf("cvSetCaptureProperty(mCapture, CV_CAP_PROP_FRAME_WIDTH,WIDTH) Failed)\n");
    }

    if (cvSetCaptureProperty(mCapture, CV_CAP_PROP_FRAME_HEIGHT,HEIGHT) == 0) {// Set camera height
        printf("cvSetCaptureProperty(mCapture, CV_CAP_PROP_FRAME_HEIGHT,HEIGHT) Failed)\n");
    }

}

int CameraReader::readCamera(Mat &image) {
    IplImage* iplCameraImage;
    iplCameraImage = cvQueryFrame(mCapture); // Get Camera image
    image = cv::cvarrToMat(iplCameraImage);  // Convert Camera image to Mat format
    
    if (IsPi3) 
        flip(image, image, -1);       // if running on PI3 flip(-1)=180 degrees

    return 0;
}


CameraReader::~CameraReader(){
    if (mCapture)
        cvReleaseCapture(&mCapture);
}