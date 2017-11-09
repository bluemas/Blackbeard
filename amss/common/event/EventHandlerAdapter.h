/*
 * EventHandlerAdapter.h
 *
 *  Created on: 2017. 11. 6.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_EVENTHANDLERADAPTER_H_
#define COMMON_EVENT_EVENTHANDLERADAPTER_H_

#include <iostream>
#include "WallRecognizerEvent.h"

class EventHandlerAdapter {
public:
    EventHandlerAdapter();
    virtual ~EventHandlerAdapter();

    virtual void wallEventHandler(const WallRecognizerEvent *) {}
    virtual void lineRecognizerEventHandler(EventBase *ev) {}
    virtual void redDotRecognizerEventHandler(EventBase *ev) {}
    virtual void signRecognizerEventHandler(EventBase *ev) {}
    virtual void squareRecognizerEventHandler(EventBase *ev) {}
};

#endif /* COMMON_EVENT_EVENTHANDLERADAPTER_H_ */
