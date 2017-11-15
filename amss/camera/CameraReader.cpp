///////////////////////////////////////////////////////////
//  CameraReader.cpp
//  Implementation of the Class CameraReader
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "CameraReader.h"
#include <unistd.h>

#define WIDTH  320
#define HEIGHT 240
#define FPS 30

// for time checking
//#define CAMERA_TIME_CHECK

#ifdef CAMERA_TIME_CHECK
#include <time.h>
static const int kCheckFrequency = 100;
static int gTimeCheckCnt = 0;
static timespec startTime;
#endif

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
    mIsCaptured = false;
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
#ifdef CAMERA_TIME_CHECK        
        timespec   currentTime;
        clock_gettime(CLOCK_MONOTONIC, &currentTime);       
        if (gTimeCheckCnt ==0 ) startTime = currentTime;
        if (++gTimeCheckCnt == kCheckFrequency) {
            time_t timeDiff = (currentTime.tv_sec - startTime.tv_sec) * 1000l + 
                    (currentTime.tv_nsec - startTime.tv_nsec)/1000000l;

            printf("average time for camera capture %ld ms\n", timeDiff/(time_t)kCheckFrequency);
            gTimeCheckCnt = 0;
        }
#endif
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
        usleep(1000);
    }
}