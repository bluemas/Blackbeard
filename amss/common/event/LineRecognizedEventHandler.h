/*
 * LineRecognizedEventHandler.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_LINERECOGNIZEDEVENTHANDLER_H_
#define COMMON_EVENT_LINERECOGNIZEDEVENTHANDLER_H_

#include "LineRecognizedEvent.h"

class LineRecognizedEventHandler {
public:
    virtual ~LineRecognizedEventHandler();
    virtual void handleLineRecognizedEvent(const LineRecognizedEvent ev) = 0;
};

#endif /* COMMON_EVENT_LINERECOGNIZEDEVENTHANDLER_H_ */
