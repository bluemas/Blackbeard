/*
 * RedDotRecognizedEventHandler.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_REDDOTRECOGNIZEDEVENTHANDLER_H_
#define COMMON_EVENT_REDDOTRECOGNIZEDEVENTHANDLER_H_

#include "RedDotRecognizedEvent.h"

class RedDotRecognizedEventHandler {
public:
    virtual ~RedDotRecognizedEventHandler();
    virtual void handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev) = 0;
};

#endif /* COMMON_EVENT_REDDOTRECOGNIZEDEVENTHANDLER_H_ */
