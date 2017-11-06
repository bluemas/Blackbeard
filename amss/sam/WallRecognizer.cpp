/*
 * WallRecognizer.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include <thread>
#include <iostream>
#include <chrono>
#include "WallRecognizer.h"

WallRecognizer::WallRecognizer(SensorDataRepo *sensorDataRepo) {
    this->mSensorDataRepo = sensorDataRepo;
}

WallRecognizer::~WallRecognizer() {
}

void WallRecognizer::init() {

}

void WallRecognizer::start() {
    mIsRun = true;

    // Start thread
    std::thread checkCollisionThread(run);
}

void WallRecognizer::stop() {
    mIsRun = false;

    // TODO thread detach???
}

void WallRecognizer::run() {
    while(mIsRun) {
        // TODO Load sensor data & check whether a collision would occur or not


        // if a collision is predicted
        //mMainControllerCallback();

        std::this_thread::sleep_for(50ms);
    }
}

void WallRecognizer::addHandler(std::function<void(int)> callback) {
    mMainControllerCallback = callback;

    // ref. https://stackoverflow.com/questions/14189440/c-class-member-callback-simple-examples
    // wallRecognizer->addHandler(std::bind(&MainController::callback, this, _1));
}
