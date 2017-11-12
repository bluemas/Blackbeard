/*
 * CrossRecognizedEventHandler.h
 *
 *  Created on: 2017. 11. 11.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_CROSSRECOGNIZEDEVENTHANDLER_H_
#define COMMON_EVENT_CROSSRECOGNIZEDEVENTHANDLER_H_

#include "CrossRecognizedEvent.h"

class CrossRecognizedEventHandler {
public:
    virtual ~CrossRecognizedEventHandler();

    virtual void handleCrossRecognizedEvent(CrossRecognizedEvent ev) = 0;
};

#endif /* COMMON_EVENT_CROSSRECOGNIZEDEVENTHANDLER_H_ */
