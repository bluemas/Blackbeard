//
// Created by lg on 11/7/17.
//

#ifndef AMSS_AUTONOMOUSESIGNRECOGNITIONMODE_H
#define AMSS_AUTONOMOUSESIGNRECOGNITIONMODE_H


#include "ModeBase.h"
#include "../common/event/EventBase.h"
#include "../common/event/EventHandlerAdapter.h"

class AutonomousSignRecognitionMode : public ModeBase {
public:
    AutonomousSignRecognitionMode(MainController* mainController);
    ~AutonomousSignRecognitionMode() {}
    void doEntryAction();

    void handleSignRecognizedEvent(const SignRecognizedEvent ev);
    void handleWallSensingEvent(const WallSensingEvent ev);
private:
    bool mSignFound;
    bool mLeftWallDetected;
    bool mFrontWallDetected;
    bool mRightWallDetected;
};


#endif //AMSS_AUTONOMOUSESIGNRECOGNITIONMODE_H
