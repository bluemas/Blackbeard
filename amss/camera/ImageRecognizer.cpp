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
    //recognize reddot
    foundDot = mDotRecog.recognizeDot(orgImg,synthImg);
    //recognize end square;
    foundSquare = mSquareRecog.recognizeSquare(orgImg,synthImg);

    // notify event to handler
    LineRecognizedEvent lineEvent(offset);
    for (unsigned int i=0; i < mLineRecogHandlers.size(); i++) {
        mLineRecogHandlers[i]->handleLineRecognizedEvent(lineEvent);
    }

    if (foundCross){
        CrossRecognizedEvent crossEvent;
        for (unsigned int i=0; i < mRedDotRecogHandlers.size(); i++) {
            mCrossRecogHandlers[i]->handleCrossRecognizedEvent(crossEvent);
        }                    
    }

    if (foundDot){
        RedDotRecognizedEvent dotEvent;
        for (unsigned int i=0; i < mRedDotRecogHandlers.size(); i++) {
            mRedDotRecogHandlers[i]->handleRedDotRecognizedEvent(dotEvent);
        }                    
    }

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
        mCamera->readCamera(orgImage);

        orgImage.copyTo(synthImage);

        if (mSignRecogEnable) {
            RecognizeSignAndNotify(orgImage, synthImage);
        } else {
            RecognizeLineDotSquareAndNotify(orgImage, synthImage);
        }

        if(!IsPi3) {
            printf("show synthImage\n");
            imshow("synthImage",synthImage);
        }

        //encode synthesized Image as Jpeg
        //store encoded Image

        imencode(".jpg", synthImage, imgWriteBuf, gJpgParam);
        mImgData->writeData(imgWriteBuf.data(), imgWriteBuf.size());
        waitKey(20);
    }
    cout << "ImageRecognizer run is finished" << endl;
}


