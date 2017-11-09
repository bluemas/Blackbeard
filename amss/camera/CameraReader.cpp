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




CameraReader::CameraReader() {
    mCapture =cvCreateCameraCapture(0);   // Open default Camera
    if(!mCapture) {
         printf("Camera Not Initialized\n");
    }
}

int CameraReader::readCamera(Mat &image) {
    
    return 0;
}


CameraReader::~CameraReader(){
    if (mCapture)
        cvReleaseCapture(&mCapture);
}