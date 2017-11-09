/*
 * EventHandlerAdapter.h
 *
 *  Created on: 2017. 11. 6.
 *      Author: gtlove
 */

#ifndef COMMON_EVENTHANDLERADAPTER_H_
#define COMMON_EVENTHANDLERADAPTER_H_

#include "EventBase.h"

class EventHandlerAdapter {
public:
    EventHandlerAdapter();
    virtual ~EventHandlerAdapter();

    virtual void wallEventHandler(EventBase *ev) {}
    virtual void lineRecognizerEventHandler(EventBase *ev) {}
    virtual void redDotRecognizerEventHandler(EventBase *ev) {}
    virtual void signRecognizerEventHandler(EventBase *ev) {}
    virtual void squareRecognizerEventHandler(EventBase *ev) {}
};

#endif /* COMMON_EVENTHANDLERADAPTER_H_ */
