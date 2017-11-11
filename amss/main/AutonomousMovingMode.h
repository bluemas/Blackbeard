///////////////////////////////////////////////////////////
//  AutonomousPathMovingMode.h
//  Implementation of the Class AutonomousPathMovingMode
//  Created on:      31-10-2017 PM 7:55:13
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !AUTONOMOUSPATHMOVINGMODE
#define AUTONOMOUSPATHMOVINGMODE

#include "ModeBase.h"
#include "../common/event/EventHandlerAdapter.h"

class AutonomousMovingMode : public ModeBase {

public:
    AutonomousMovingMode(MainController* mainController);
    ~AutonomousMovingMode() {}

    void handleCollisionEvent(const WallCollisionEvent ev);
    void handleWallSensingEvent(const WallSensingEvent ev);
    void handleLineRecognizedEvent(const LineRecognizedEvent ev);
    void handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev);
};
#endif
