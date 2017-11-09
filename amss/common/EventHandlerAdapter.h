/*
 * EventHandlerAdapter.h
 *
 *  Created on: 2017. 11. 6.
 *      Author: gtlove
 */

#ifndef COMMON_EVENTHANDLERADAPTER_H_
#define COMMON_EVENTHANDLERADAPTER_H_

#include <iostream>
#include "WallRecognizerEvent.h"

class EventHandlerAdapter {
public:
    EventHandlerAdapter();
    virtual ~EventHandlerAdapter();

<<<<<<< HEAD
    virtual void wallEventHandler(EventBase *ev) {}
    virtual void lineRecognizerEventHandler(EventBase *ev) {}
    virtual void redDotRecognizerEventHandler(EventBase *ev) {}
    virtual void signRecognizerEventHandler(EventBase *ev) {}
    virtual void squareRecognizerEventHandler(EventBase *ev) {}
=======
    virtual void wallEventHandler(const WallRecognizerEvent *);
>>>>>>> 3e0449a007b1dcf45cf16fc41104f6677b9ac2c0
};

#endif /* COMMON_EVENTHANDLERADAPTER_H_ */
