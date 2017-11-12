///////////////////////////////////////////////////////////
//  ManualMode.h
//  Implementation of the Class ManualMode
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_D7F4455E_FAA3_42b8_9887_D9E5F1BD2D0C__INCLUDED_)
#define EA_D7F4455E_FAA3_42b8_9887_D9E5F1BD2D0C__INCLUDED_

#include "ModeBase.h"
#include "../common/event/EventHandlerAdapter.h"
#include "../network/NetMessageEventAdapter.h"

class ManualMode : public ModeBase {
public:
    ManualMode(MainController* mainController);
    ~ManualMode() {}

    void doEntryAction();
    void doExitAction();

    void adjustCamera(char direction);
    void moveRobot(char direction);

    void handleCollisionEvent(WallCollisionEvent ev);
    void handleRedDotRecognizedEvent(RedDotRecognizedEvent ev);
    void handleSignRecognizedEvent(SignRecognizedEvent ev);
};
#endif // !defined(EA_D7F4455E_FAA3_42b8_9887_D9E5F1BD2D0C__INCLUDED_)
