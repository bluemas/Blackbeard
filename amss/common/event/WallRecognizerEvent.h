/*
 * WallRecognizerEvent.h
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_WALLRECOGNIZEREVENT_H_
#define COMMON_EVENT_WALLRECOGNIZEREVENT_H_

#include "EventBase.h"

class WallRecognizerEvent: public EventBase {
public:
    WallRecognizerEvent();
    virtual ~WallRecognizerEvent();
};

#endif /* COMMON_EVENT_WALLRECOGNIZEREVENT_H_ */
