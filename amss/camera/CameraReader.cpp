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
using namespace std;

CameraReader::CameraReader()
        : mIsRun(false),
          mIsCaptured(false) {
//    printf("camera reader constructor\n");
    mCapture = cvCreateCameraCapture(0);   // Open default Camera
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
    
    std::unique_lock<std::mutex> lock(mMutex);
    while (!mIsCaptured)
        mCondition.wait(lock);
    mImg.copyTo(image);

    return 0;
}


CameraReader::~CameraReader(){
    if (mCapture)
        cvReleaseCapture(&mCapture);
}

void CameraReader::start() {
    cout << "CameraReader thread started" << endl;
    mIsRun = true;

    // Start thread
    mThread = std::thread(&CameraReader::run, this);
}

void CameraReader::stop() {
    mIsRun = false;

    mThread.join();
    cout << "CameraReader thread is terminated" << endl;
}

void CameraReader::run() {
    IplImage* iplCameraImage;
    printf("Camera reader run\n");
    while (mIsRun) {
        iplCameraImage = cvQueryFrame(mCapture); // Get Camera image
        {
            std::lock_guard<std::mutex> lock(mMutex);

            mImg = cv::cvarrToMat(iplCameraImage);  // Convert Camera image to Mat format
            
            if (IsPi3) 
                flip(mImg, mImg, -1);       // if running on PI3 flip(-1)=180 degrees
           // printf("Camera reader caputred\n");
            mIsCaptured = true;
            mCondition.notify_all();
        }
    }
}