/*
 * SquareRecognizedEventHandler.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_SQUARERECOGNIZEDEVENTHANDLER_H_
#define COMMON_EVENT_SQUARERECOGNIZEDEVENTHANDLER_H_

#include "SquareRecognizedEvent.h"

class SquareRecognizedEventHandler {
public:
    virtual ~SquareRecognizedEventHandler();
    virtual void handleSquareRecognizedEvent(const SquareRecognizedEvent ev) = 0; // REVIEW : const »èÁ¦(Á¤À±½Ä, ±èÁö¼º)
};

#endif /* COMMON_EVENT_SQUARERECOGNIZEDEVENTHANDLER_H_ */
