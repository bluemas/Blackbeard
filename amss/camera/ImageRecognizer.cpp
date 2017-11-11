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


ImageRecognizer::ImageRecognizer()
        : mMode(RobotMode::None) {
    mCamera = new CameraReader();
}

ImageRecognizer::~ImageRecognizer(){
    stop();    
    if(mCamera)
        delete mCamera;

}

void ImageRecognizer::start() {
    mIsRun = true;

    // Start thread
    mThread = std::thread(&ImageRecognizer::run, this);
}

void ImageRecognizer::stop() {
    mIsRun = false;

    mThread.join();

    cout << "ImageRecognizer thread is terminated" << endl;
    // TODO thread detach???
}

void ImageRecognizer::addLineRecogEventHandler(LineRecognizedEventHandler *eventHandler) {
    mLineRecogHandlers.push_back(eventHandler);

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

void ImageRecognizer::setRobotMode(RobotMode mode) {
    mMode = mode;
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
    float offset = 0.0;

    //recognize line
    offset = mLineRecog.calculateLineOffset(orgImg,synthImg);
    //recognize reddot
    foundDot = mDotRecog.recognizeDot(orgImg,synthImg);
    //recognize end square;
    foundSquare = mSquareRecog.recognizeSquare(orgImg,synthImg);

    // notify event to handler
    LineRecognizedEvent lineEvent(offset);
    for (unsigned int i=0; i < mLineRecogHandlers.size(); i++) {
        mLineRecogHandlers[i]->handleLineRecognizedEvent(lineEvent);
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

    while (mIsRun) {
        // read Camera image
        mCamera->readCamera(orgImage);
        orgImage.copyTo(synthImage);

        switch(mMode) {
            case RobotMode::Manual:
            case RobotMode::AutoSignRecognition:
                RecognizeSignAndNotify(orgImage, synthImage);
                break;
            case RobotMode::AutoMoving: 
                RecognizeLineDotSquareAndNotify(orgImage, synthImage);
                break;
            default:
                break;
        }

        //encode synthesized Image as Jpeg
        //store encoded Image
    }

}


