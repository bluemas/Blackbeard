/*
 * WallRecognizer.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "WallRecognizer.h"

WallRecognizer::WallRecognizer() {
    mMazeMapper = NULL;
    mSensorData = SensorData::getInstance();

    mSonarFront = new SonarFront();
    mFlightSensorLeft = new FlightSensorLeft();
    mFlightSensorRight = new FlightSensorRight();
}

WallRecognizer::~WallRecognizer() {
    delete mSonarFront;
    delete mFlightSensorLeft;
    delete mFlightSensorRight;
}

void WallRecognizer::setMazeMapper(MazeMapper *mazeMapper) {
    mMazeMapper = mazeMapper;
}

void WallRecognizer::addWallCollisionEventHandler(WallCollisionEventHandler *eventHandler) {
    mWallCollisionEventHandlers.push_back(eventHandler);
}

void WallRecognizer::addWallSensingEventHandler(WallSensingEventHandler *eventHandler) {
    mWallSensingEventHandlers.push_back(eventHandler);
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
        #ifndef UBUNTU
        mSonarFront->read();
        mFlightSensorLeft->read();
        mFlightSensorRight->read();

        int frontDistance = mSensorData->getData(SensorType::front);
        int leftDistance = mSensorData->getData(SensorType::left);
        int rightDistance = mSensorData->getData(SensorType::right);

        // Check whether a collision would be occur
        WallCollisionEvent wallCollisionEvent =
                checkCollision(frontDistance, leftDistance, rightDistance);

        if (wallCollisionEvent.isWarnCollision()) {
            // Notify to MainController
            for(WallCollisionEventHandler *handler : mWallCollisionEventHandlers) {
                // TODO async call
                handler->handleWallCollisionEvent(wallCollisionEvent);
            }
        }

        // Check wall status in this position
        WallSensingEvent wallSensingEvent =
                checkWallStatus(frontDistance, leftDistance, rightDistance);

        // Notify to WallSensingEventHandlers
        for(WallSensingEventHandler *handler : mWallSensingEventHandlers) {
            // TODO async call
            handler->handleWallSensingEvent(wallSensingEvent);
        }
        #endif

        // Sleep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(SENSING_PERIOD_IN_MS));
    }
}

WallCollisionEvent WallRecognizer::checkCollision(
        int frontDistance, int leftDistance, int rightDistance) {

    // Check whether a collision is predicted
    WallCollisionEvent ev;

    if (frontDistance < MIN_FRONT_COLLISION_DISTANCE) {
        ev.setFrontDistance(frontDistance);
    }

    if (leftDistance < MIN_SIDE_COLLISION_DISTANCE) {
        ev.setRightDistance(leftDistance);
    }

    if (rightDistance < MIN_SIDE_COLLISION_DISTANCE) {
        ev.setRightDistance(rightDistance);
    }

    if (ev.isWarnCollision()) {
        cout << "Warn collision. " << "Front : " << frontDistance << ", Left : " << leftDistance
                << ", Right : " << rightDistance << endl;
    }

    return ev;
}

WallSensingEvent WallRecognizer::checkWallStatus(
        int frontDistance, int leftDistance, int rightDistance) {

    WallSensingEvent ev;

    if (frontDistance < MIN_FRONT_WALL_DISTANCE) {
        // There is the wall in front
        ev.setFrontWall();
    }

    if (leftDistance < MIN_SIDE_WALL_DISTANCE) {
        // There is the wall in left
        ev.setLeftWall();
    }

    if (rightDistance < MIN_SIDE_WALL_DISTANCE) {
        // there is the wall in right
        ev.setRightWall();
    }

    return ev;
}
