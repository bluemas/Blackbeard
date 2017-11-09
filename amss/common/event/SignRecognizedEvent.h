/*
 * SignRecognizedEvent.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_SIGNRECOGNIZEDEVENT_H_
#define COMMON_EVENT_SIGNRECOGNIZEDEVENT_H_

#include "EventBase.h"

class SignRecognizedEvent : public EventBase {
public:
    SignRecognizedEvent();
    virtual ~SignRecognizedEvent();
};

#endif /* COMMON_EVENT_SIGNRECOGNIZEDEVENT_H_ */
