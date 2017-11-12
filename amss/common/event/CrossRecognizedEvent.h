/*
 * CrossRecognizedEvent.h
 *
 *  Created on: 2017. 11. 11.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_CROSSRECOGNIZEDEVENT_H_
#define COMMON_EVENT_CROSSRECOGNIZEDEVENT_H_

#include "EventBase.h"

class CrossRecognizedEvent : public EventBase {
public:
    CrossRecognizedEvent();
    virtual ~CrossRecognizedEvent();
};

#endif /* COMMON_EVENT_CROSSRECOGNIZEDEVENT_H_ */
