/*
 * LineRecognizedEvent.cpp
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#include "LineRecognizedEvent.h"

LineRecognizedEvent::~LineRecognizedEvent() {
    // TODO Auto-generated destructor stub
}

LineRecognizedEvent::LineRecognizedEvent(float offset)
        : mOffset(offset) {
    // TODO Auto-generated constructor stub
}

float LineRecognizedEvent::getOffset() {
    return mOffset;
}