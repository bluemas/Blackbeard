///////////////////////////////////////////////////////////
//  ImageRecognizer.h
//  Implementation of the Class ImageRecognizer
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(_ImageRecognizer_H_)
#define _ImageRecognizer_H_


#include "CameraReader.h"
#include "../common/event/LineRecognizedEventHandler.h"
#include "../common/event/CrossRecognizedEventHandler.h"
#include "../common/event/RedDotRecognizedEventHandler.h"
#include "../common/event/SignRecognizedEventHandler.h"
#include "../common/event/SquareRecognizedEventHandler.h"
#include "../common/event/EventHandlerAdapter.h"
#include "../common/Constants.h"

#include "DotRecognizer.h"
#include "LineRecognizer.h"
#include "SignRecognizer.h"
#include "SquareRecognizer.h"
#include "ImageData.h"

#include <thread>

using namespace std;


class ImageRecognizer
{

public:
    ImageRecognizer();
    virtual ~ImageRecognizer();
    void addLineRecogEventHandler(LineRecognizedEventHandler *eventHandler);
    void addCrossRecogEventHandler(CrossRecognizedEventHandler *eventHandler);
    void addRedDotRecogEventHandler(RedDotRecognizedEventHandler *eventHandler);
    void addSignRecogEventHandler(SignRecognizedEventHandler *eventHandler);
    void addSquareRecogEventHandler(SquareRecognizedEventHandler *eventHandler);
    void setSignRecognizeMode(bool enable);
    void setLineRecognizeMode(bool enable);
    void start();
    void stop();


private:
    CameraReader *mCamera;
    DotRecognizer mDotRecog;
    LineRecognizer mLineRecog;
    SignRecognizer mSignRecog;
    SquareRecognizer mSquareRecog;
    ImageData *mImgData;

    bool mIsRun;
    std::thread mThread;

    vector<LineRecognizedEventHandler*> mLineRecogHandlers;
    vector<CrossRecognizedEventHandler*> mCrossRecogHandlers;
    vector<RedDotRecognizedEventHandler*> mRedDotRecogHandlers;
    vector<SignRecognizedEventHandler*> mSignRecogHandlers;
    vector<SquareRecognizedEventHandler*> mSquareRecogHandlers;

    bool mSignRecogEnable;
    bool mLineRecogEnable;

    void run();
    void RecognizeLineDotSquareAndNotify(Mat& orgImg, Mat& synthImg);
    void RecognizeSignAndNotify(Mat& orgImg, Mat& synthImg);
};
#endif // !defined(_ImageRecognizer_H_)
