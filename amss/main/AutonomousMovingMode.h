///////////////////////////////////////////////////////////
//  AutonomousPathMovingMode.h
//  Implementation of the Class AutonomousPathMovingMode
//  Created on:      31-10-2017 PM 7:55:13
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !AUTONOMOUSPATHMOVINGMODE
#define AUTONOMOUSPATHMOVINGMODE

#include "ModeBase.h"
#include "../common/EventHandlerAdapter.h"

class AutonomousMovingMode : public ModeBase, public EventHandlerAdapter {

public:
    AutonomousMovingMode(MainController* mainController);
    ~AutonomousMovingMode() {}

    void wallEventHandler(EventBase *ev);
    void lineRecognizerEventHandler(EventBase *ev);
    void redDotRecognizerEventHandler(EventBase *ev);
    void squareRecognizerEventHandler(EventBase *ev);
};
#endif
