/*
 * LineRecognizedEvent.cpp
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#include "LineRecognizedEvent.h"

LineRecognizedEvent::~LineRecognizedEvent() {
}

LineRecognizedEvent::LineRecognizedEvent(float offset)
        : mOffset(offset) {
}

float LineRecognizedEvent::getOffset() {
    return mOffset;
}