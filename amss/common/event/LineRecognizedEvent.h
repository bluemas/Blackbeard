/*
 * LineRecognizedEvent.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_LINERECOGNIZEDEVENT_H_
#define COMMON_EVENT_LINERECOGNIZEDEVENT_H_

#include "EventBase.h"

class LineRecognizedEvent : public EventBase {
public:
    virtual ~LineRecognizedEvent();
    LineRecognizedEvent(float offset);
    float getOffset();

private:
    float mOffset;
};

#endif /* COMMON_EVENT_LINERECOGNIZEDEVENT_H_ */
