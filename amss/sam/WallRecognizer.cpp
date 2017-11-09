/*
 * WallRecognizer.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "WallRecognizer.h"

WallRecognizer::WallRecognizer() {
    mSensorData = SensorData::getInstance();
    mSonarFront = new SonarFront();
    mFlightSensorLeft = new FlightSensorLeft();
    mFlightSensorRight = new FlightSensorRight();
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
        mSonarFront->read();
        mFlightSensorLeft->read();
        mFlightSensorRight->read();

        double frontDistance = mSensorData->getData(SensorType::front);
        double leftDistance = mSensorData->getData(SensorType::left);
        double rightDistance = mSensorData->getData(SensorType::right);

        checkCollision(frontDistance, leftDistance, rightDistance);
        checkWall(frontDistance, leftDistance, rightDistance);

        std::this_thread::sleep_for(std::chrono::milliseconds(SENSING_PERIOD_IN_MS));
    }
}

void WallRecognizer::addEventHandler(EventHandlerAdapter *eventHandler) {
    // TODO mEventHandler ventor vector->push(eventHandler);
    mEventHandler = eventHandler;
}

void WallRecognizer::checkCollision(double frontDistance, double leftDistance, double rightDistance) {
    // Check whether a collision is predicted
    bool isPredictCollision = false;
    WallRecognizerEvent *ev = new WallRecognizerEvent();

    if (frontDistance < MIN_FRONT_COLLISION_DISTANCE) {
        // if a collision is predicted
        isPredictCollision = true;
    }

    if (leftDistance < MIN_SIDE_COLLISION_DISTANCE) {
        isPredictCollision = true;
    }

    if (rightDistance < MIN_SIDE_COLLISION_DISTANCE) {
        isPredictCollision = true;
    }

    if (isPredictCollision) {
        cout << "Front : " << frontDistance << ", Left : " << leftDistance
                << ", Right : " << rightDistance << endl;

        mEventHandler->wallEventHandler(ev);
    }

    delete ev;
}

void WallRecognizer::checkWall(double frontDistance, double leftDistance, double rightDistace) {
    unsigned char wallStatus = 0;

    if (frontDistance < MIN_FRONT_DISTANCE) {
        // There is the wall in front
        wallStatus |= 0;
    }

    if (leftDistance < MIN_SIDE_DISTANCE) {
        // There is the wall in left
        wallStatus |= 1;
    }

    if (leftDistance < MIN_SIDE_DISTANCE) {
        // there is the wall in right
        wallStatus |= 2;
    }

    // TODO Send current wall status to MazeMapper
}
