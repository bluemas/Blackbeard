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

    void handleCollisionEvent(WallCollisionEvent ev);
    void handleWallSensingEvent(WallSensingEvent ev);
    void handleLineRecognizedEvent(LineRecognizedEvent ev);
    void handleRedDotRecognizedEvent(RedDotRecognizedEvent ev);
    void handleCrossRecognizedEvent(CrossRecognizedEvent ev);
};
#endif
