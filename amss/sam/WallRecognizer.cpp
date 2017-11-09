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
    ~mSonarFront();
    ~mFlightSensorLeft();
    ~mFlightSensorRight();
}

void WallRecognizer::setMazeMapper(MazeMapper *mazeMapper) {
    mMazeMapper = mazeMapper;
}

void WallRecognizer::addEventHandler(EventHandlerAdapter *eventHandler) {
    // TODO mEventHandler ventor vector->push(eventHandler);
    mEventHandler = eventHandler;
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

        // Check whether a collision would be occur
        WallRecognizerEvent *warnCollisionEvent =
                checkCollision(frontDistance, leftDistance, rightDistance);

        if (warnCollisionEvent) {
            // Notify to MainController
            mEventHandler->wallEventHandler(warnCollisionEvent);
        }

        delete warnCollisionEvent;

        // Check wall status in this position
        WallSensingEvent* wallSensingEvent =
                checkWallStatus(frontDistance, leftDistance, rightDistance);

        // Notify to MazeMapper
        mMazeMapper->updateWallSensingEvent(wallSensingEvent);

        delete wallSensingEvent;


        // Sleep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(SENSING_PERIOD_IN_MS));
    }
}

WallRecognizerEvent* WallRecognizer::checkCollision(
        double frontDistance, double leftDistance, double rightDistance) {

    // Check whether a collision is predicted
    WallRecognizerEvent *ev;

    if (frontDistance < MIN_FRONT_COLLISION_DISTANCE) {
        // if a collision is predicted
        if (!ev) {
            ev = new WallRecognizerEvent();
        }

        // TOOD set additional info
    }

    if (leftDistance < MIN_SIDE_COLLISION_DISTANCE) {
        if (!ev) {
            ev = new WallRecognizerEvent();
        }

        // TOOD set additional info
    }

    if (rightDistance < MIN_SIDE_COLLISION_DISTANCE) {
        if (!ev) {
            ev = new WallRecognizerEvent();
        }

        // TOOD set additional info
    }

    if (ev) {
        cout << "Front : " << frontDistance << ", Left : " << leftDistance
                << ", Right : " << rightDistance << endl;
    }

    return ev;
}

WallSensingEvent* WallRecognizer::checkWallStatus(
        double frontDistance, double leftDistance, double rightDistace) {

    unsigned char wallStatus = 0;

    if (frontDistance < MIN_FRONT_DISTANCE) {
        // There is the wall in front
        wallStatus |= WallStatus::front;
    }

    if (leftDistance < MIN_SIDE_DISTANCE) {
        // There is the wall in left
        wallStatus |= WallStatus::left;
    }

    if (leftDistance < MIN_SIDE_DISTANCE) {
        // there is the wall in right
        wallStatus |= WallStatus::right;
    }

    WallSensingEvent *ev = new WallSensingEvent(wallStatus);

    return ev;
}
