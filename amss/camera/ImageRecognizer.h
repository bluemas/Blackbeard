///////////////////////////////////////////////////////////
//  ImageRecognizer.h
//  Implementation of the Class ImageRecognizer
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(_ImageRecognizer_H_)
#define _ImageRecognizer_H_


#include "CameraReader.h"
#include <event/LineRecognizedEventHandler.h>
#include <event/RedDotRecognizedEventHandler.h>
#include <event/SignRecognizedEventHandler.h>
#include <event/SquareRecognizedEventHandler.h>
#include <event/EventHandlerAdapter.h>
#include <Constants.h>

#include "DotRecognizer.h"
#include "LineRecognizer.h"
#include "SignRecognizer.h"
#include "SquareRecognizer.h"

#include <thread>

using namespace std;


class ImageRecognizer
{

public:
    ImageRecognizer();
    virtual ~ImageRecognizer();
    void addLineRecogEventHandler(LineRecognizedEventHandler *eventHandler);
    void addRedDotRecogEventHandler(RedDotRecognizedEventHandler *eventHandler);
    void addSignRecogEventHandler(SignRecognizedEventHandler *eventHandler);
    void addSquareRecogEventHandler(SquareRecognizedEventHandler *eventHandler);
    void setRobotMode(RobotMode mode);
    void start();
    void stop();


private:
    CameraReader *mCamera;
    DotRecognizer mDotRecog;
    LineRecognizer mLineRecog;
    SignRecognizer mSignRecog;
    SquareRecognizer mSquareRecog;

    bool mIsRun;
    std::thread mThread;

    vector<LineRecognizedEventHandler*> mLineRecogHandlers;
    vector<RedDotRecognizedEventHandler*> mRedDotRecogHandlers;
    vector<SignRecognizedEventHandler*> mSignRecogHandlers;
    vector<SquareRecognizedEventHandler*> mSquareRecogHandlers;

    RobotMode mMode;

    void run();
    void RecognizeLineDotSquareAndNotify(Mat& orgImg, Mat& synthImg);
    void RecognizeSignAndNotify(Mat& orgImg, Mat& synthImg);
};
#endif // !defined(_ImageRecognizer_H_)
