//
// Created by lg on 11/7/17.
//

#ifndef AMSS_AUTONOMOUSESIGNRECOGNITIONMODE_H
#define AMSS_AUTONOMOUSESIGNRECOGNITIONMODE_H


#include "ModeBase.h"
#include "../common/event/EventBase.h"
#include "../common/event/EventHandlerAdapter.h"

class AutonomousSignRecognitionMode : public ModeBase, public EventHandlerAdapter {
public:
    AutonomousSignRecognitionMode(MainController* mainController);
    ~AutonomousSignRecognitionMode() {}
    void doEntryAction();

    void signRecognizerEventHandler(EventBase *ev);
private:
    bool mSignFound;
};


#endif //AMSS_AUTONOMOUSESIGNRECOGNITIONMODE_H
