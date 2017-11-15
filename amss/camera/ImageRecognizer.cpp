///////////////////////////////////////////////////////////
//  ImageRecognizer.cpp
//  Implementation of the Class ImageRecognizer
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluem
///////////////////////////////////////////////////////////

#include "ImageRecognizer.h"
#include "../common/Constants.h"
#include "../common/event/LineRecognizedEventHandler.h"
#include "../common/event/RedDotRecognizedEventHandler.h"
#include "../common/event/SignRecognizedEventHandler.h"
#include "../common/event/SquareRecognizedEventHandler.h"

// for time checking
//#define IMG_RECOG_TIME_CHECK

#ifdef IMG_RECOG_TIME_CHECK
#include <time.h>
static const int kCheckFrequency = 100;
static int gTimeCheckCnt = 0;
static timespec startTime;
#endif

static  int gInitJpgValues[2] = { cv::IMWRITE_JPEG_QUALITY,80 }; //default(95) 0-100
static  std::vector<int> gJpgParam (&gInitJpgValues[0], &gInitJpgValues[0]+2);



ImageRecognizer::ImageRecognizer()
        : mSignRecogEnable(false),
          mLineRecogEnable(false) {
    mCamera = new CameraReader();
    mImgData = ImageData::getInstance();
}

ImageRecognizer::~ImageRecognizer(){
    stop();
    if(mCamera)
        delete mCamera;

}

void ImageRecognizer::start() {
    cout << "ImageRecognizer thread started" << endl;
    mIsRun = true;
    mCamera->start();

    // Start thread
    mThread = std::thread(&ImageRecognizer::run, this);
}

void ImageRecognizer::stop() {
    mIsRun = false;

    mThread.join();
    cout << "ImageRecognizer thread is terminated" << endl;
    mCamera->stop();
    // TODO thread detach???
}

void ImageRecognizer::addLineRecogEventHandler(LineRecognizedEventHandler *eventHandler) {
    mLineRecogHandlers.push_back(eventHandler);
}

void ImageRecognizer::addCrossRecogEventHandler(CrossRecognizedEventHandler *eventHandler) {
    mCrossRecogHandlers.push_back(eventHandler);
}
void ImageRecognizer::addRedDotRecogEventHandler(RedDotRecognizedEventHandler *eventHandler) {
    mRedDotRecogHandlers.push_back(eventHandler);
}

void ImageRecognizer::addSignRecogEventHandler(SignRecognizedEventHandler *eventHandler) {
    mSignRecogHandlers.push_back(eventHandler);
}

void ImageRecognizer::addSquareRecogEventHandler(SquareRecognizedEventHandler *eventHandler) {
    mSquareRecogHandlers.push_back(eventHandler);
}

void ImageRecognizer::setSignRecognizeMode(bool enable) {
    mSignRecogEnable = enable;
}

void ImageRecognizer::setLineRecognizeMode(bool enable) {
    mLineRecogEnable = enable;
}

void ImageRecognizer::RecognizeSignAndNotify(Mat& orgImg, Mat& synthImg) {
    SignType sign = SignType::SignNone;
    //Recognize sign
    sign = mSignRecog.recognizeSign(orgImg,synthImg);

    //notify event to handler
    if (sign != SignType::SignNone) {
        SignRecognizedEvent signEvent(sign);
        for (unsigned int i=0; i < mSignRecogHandlers.size(); i++) {
            mSignRecogHandlers[i]->handleSignRecognizedEvent(signEvent);
        }
    }
}


void ImageRecognizer::RecognizeLineDotSquareAndNotify(Mat& orgImg, Mat& synthImg) {
    bool foundSquare = false;
    bool foundDot = false;
    bool foundCross = false;
    float offset = 0.0;

    //recognize line
    offset = mLineRecog.calculateLineOffset(orgImg,synthImg, foundCross);

    // notify event to handler
    LineRecognizedEvent lineEvent(offset);
    for (unsigned int i=0; i < mLineRecogHandlers.size(); i++) {
        mLineRecogHandlers[i]->handleLineRecognizedEvent(lineEvent);
    }

    //recognize reddot
    foundDot = mDotRecog.recognizeDot(orgImg,synthImg);

    if (foundDot) {
        RedDotRecognizedEvent dotEvent;
        for (unsigned int i=0; i < mRedDotRecogHandlers.size(); i++) {
            mRedDotRecogHandlers[i]->handleRedDotRecognizedEvent(dotEvent);
        }

        return;
    }

    //recognize end square;
    if (!foundDot) {
        foundSquare = mSquareRecog.recognizeSquare(orgImg,synthImg);
    }

//    if (foundCross){
//        CrossRecognizedEvent crossEvent;

#if 0 // for Dump
            static int sCnt=0;
            char fileName[256];
            sprintf(fileName, "img_%d.jpg", sCnt++);
            imwrite(fileName, orgImg);
#endif

//        for (unsigned int i=0; i < mCrossRecogHandlers.size(); i++) {
//            mCrossRecogHandlers[i]->handleCrossRecognizedEvent(crossEvent);
//        }
//    }

    if (foundSquare) {
        SquareRecognizedEvent squareEvent;
        for (unsigned int i=0; i < mSquareRecogHandlers.size(); i++) {
            mSquareRecogHandlers[i]->handleSquareRecognizedEvent(squareEvent);
        }
    }
}


void ImageRecognizer::run() {
    Mat orgImage;
    Mat synthImage;
    std::vector<uchar> imgWriteBuf;


    if(!IsPi3) {
        printf("create synth image\n");
        namedWindow("synthImage", CV_WINDOW_AUTOSIZE);
    }
    while (mIsRun) {
        // read Camera image
#ifdef IMG_RECOG_TIME_CHECK        
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
        // read Camera image

        mCamera->readCamera(orgImage);

        orgImage.copyTo(synthImage);

        if (mSignRecogEnable) {
            RecognizeSignAndNotify(orgImage, synthImage);
        } else if (mLineRecogEnable) {
            //printf("line recog\n");
            RecognizeLineDotSquareAndNotify(orgImage, synthImage);
        }

        if(!IsPi3) {
            imshow("synthImage",synthImage);
        }

        //encode synthesized Image as Jpeg
        //store encoded Image

        imencode(".jpg", synthImage, imgWriteBuf, gJpgParam);
        mImgData->writeData(imgWriteBuf.data(), imgWriteBuf.size());
        waitKey(10);
    }
    cout << "ImageRecognizer run is finished" << endl;
}


