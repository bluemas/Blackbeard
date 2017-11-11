/*
 * SignRecognizedEventHandler.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_SIGNRECOGNIZEDEVENTHANDLER_H_
#define COMMON_EVENT_SIGNRECOGNIZEDEVENTHANDLER_H_

#include "SignRecognizedEvent.h"

class SignRecognizedEventHandler {
public:
    virtual ~SignRecognizedEventHandler();
    virtual void handleSignRecognizedEvent(SignRecognizedEvent ev) = 0;

};

#endif /* COMMON_EVENT_SIGNRECOGNIZEDEVENTHANDLER_H_ */
