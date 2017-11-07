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

    void wallEventHandler(EventBase *);
};

#endif /* COMMON_EVENTHANDLERADAPTER_H_ */
