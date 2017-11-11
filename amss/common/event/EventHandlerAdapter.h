/*
 * EventHandlerAdapter.h
 *
 *  Created on: 2017. 11. 6.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_EVENTHANDLERADAPTER_H_
#define COMMON_EVENT_EVENTHANDLERADAPTER_H_

#include <iostream>

#include "WallCollisionEventHandler.h"
#include "WallSensingEventHandler.h"
#include "LineRecognizedEventHandler.h"
#include "RedDotRecognizedEventHandler.h"
#include "SignRecognizedEventHandler.h"
#include "SquareRecognizedEventHandler.h"

class EventHandlerAdapter : public WallCollisionEventHandler,
                            public WallSensingEventHandler,
                            public LineRecognizedEventHandler,
                            public RedDotRecognizedEventHandler,
                            public SignRecognizedEventHandler,
                            public SquareRecognizedEventHandler {
public:
    EventHandlerAdapter();
    virtual ~EventHandlerAdapter();

    virtual void handleCollisionEvent(WallCollisionEvent ev) {}
    virtual void handleWallSensingEvent(WallSensingEvent ev) {}
    virtual void handleLineRecognizedEvent(LineRecognizedEvent ev) {}
    virtual void handleRedDotRecognizedEvent(RedDotRecognizedEvent ev) {}
    virtual void handleSignRecognizedEvent(SignRecognizedEvent ev) {}
    virtual void handleSquareRecognizedEvent(SquareRecognizedEvent ev) {}
};

#endif /* COMMON_EVENT_EVENTHANDLERADAPTER_H_ */
