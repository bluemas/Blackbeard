/*
 * WallRecognizer.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "WallRecognizer.h"

WallRecognizer::WallRecognizer() {

}

WallRecognizer::~WallRecognizer() {
}

void WallRecognizer::init() {

}

void WallRecognizer::start() {
    mIsRun = true;

    // Start thread
    mThread = std::thread(&WallRecognizer::run, this);
}

void WallRecognizer::stop() {
    mIsRun = false;

    // Wait for thread stopping
    mThread.join();

    cout << "WallRecognizer thread is terminated" << endl;
    // TODO thread detach???
}

void WallRecognizer::run() {
    // Waiting for start main thread
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    while(mIsRun) {
        // TODO Load sensor data & check whether a collision would occur or not

        // if a collision is predicted
        EventBase *ev = new WallRecognizerEvent();
        mEventHandler(ev);

        delete ev;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void WallRecognizer::addEventHandler(std::function<void(EventBase*)> eventHandler) {
    // TODO Manage event handlers into Vector so that it enables to add a number of event handlers in recognizer => Modifiability
    mEventHandler = eventHandler;
}
