/*
 * SignRecognizedEvent.cpp
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#include "SignRecognizedEvent.h"

SignRecognizedEvent::SignRecognizedEvent(SignType sign)
        :mSign(sign) {

}

SignRecognizedEvent::~SignRecognizedEvent() {

}

SignType SignRecognizedEvent::getSignType() {
    return mSign;
}

