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


void WallRecognizer::start() {
    mIsRun = true;

    // Start thread
    mThread = std::thread(&WallRecognizer::run, this);
}

void WallRecognizer::stop() {
    mIsRun = false;

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

        std::future<void> result (std::async(mEventHandler, ev));

        result.wait();
        delete ev;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void WallRecognizer::addEventHandler(std::function<void(const EventBase*)> eventHandler) {
    // TODO mEventHandler ventor vector->push(wallRecognizerEventHandler);
    mEventHandler = eventHandler;
}
