/*
 * EventHandlerAdapter.cpp
 *
 *  Created on: 2017. 11. 6.
 *      Author: gtlove
 */

#include "EventHandlerAdapter.h"

EventHandlerAdapter::EventHandlerAdapter() {

}

EventHandlerAdapter::~EventHandlerAdapter() {

}

void EventHandlerAdapter::wallEventHandler(const WallRecognizerEvent *) {
    std::cout << "In EventHandlerAdapter" << std::endl;
}
