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
    delete mSonarFront;
    delete mFlightSensorLeft;
    delete mFlightSensorRight;
}

void WallRecognizer::setMazeMapper(MazeMapper *mazeMapper) {
    mMazeMapper = mazeMapper;
}

void WallRecognizer::addWallCollisionEventHandler(WallCollisionEventHandler *eventHandler) {
    // TODO mEventHandler vector vector->push(eventHandler);
    mWallCollisionEventHandler = eventHandler;
}

void WallRecognizer::addWallSensingEventHandler(WallSensingEventHandler *eventHandler) {
    // TODO mEventHandler vector vector->push(eventHandler);
    mWallSensingEventHandler = eventHandler;
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

        int frontDistance = mSensorData->getData(SensorType::front);
        int leftDistance = mSensorData->getData(SensorType::left);
        int rightDistance = mSensorData->getData(SensorType::right);

        // Check whether a collision would be occur
        WallCollisionEvent wallColisionEvent =
                checkCollision(frontDistance, leftDistance, rightDistance);

        if (wallColisionEvent.isWarnCollision()) {
            // Notify to MainController
            mWallCollisionEventHandler->handleWallCollisionEvent(wallColisionEvent);
        }

        // Check wall status in this position
        WallSensingEvent wallSensingEvent =
                checkWallStatus(frontDistance, leftDistance, rightDistance);

        // Notify to MazeMapper
        mMazeMapper->handleWallSensingEvent(wallSensingEvent);


        // Sleep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(SENSING_PERIOD_IN_MS));
    }
}

WallCollisionEvent WallRecognizer::checkCollision(
        double frontDistance, double leftDistance, double rightDistance) {

    // Check whether a collision is predicted
    WallCollisionEvent ev;

    if (frontDistance < MIN_FRONT_COLLISION_DISTANCE) {
        ev.setFrontDistance(1);
    }

    if (leftDistance < MIN_SIDE_COLLISION_DISTANCE) {
        ev.setRightDistance(1);
    }

    if (rightDistance < MIN_SIDE_COLLISION_DISTANCE) {
        ev.setRightDistance(1);
    }

    if (ev.isWarnCollision()) {
        cout << "Front : " << frontDistance << ", Left : " << leftDistance
                << ", Right : " << rightDistance << endl;
    }

    return ev;
}

WallSensingEvent WallRecognizer::checkWallStatus(
        double frontDistance, double leftDistance, double rightDistace) {

    unsigned char wallStatus = 0;

    if (frontDistance < MIN_FRONT_DISTANCE) {
        // There is the wall in front
        wallStatus |= static_cast<unsigned char>(WallStatus::front);
    }

    if (leftDistance < MIN_SIDE_DISTANCE) {
        // There is the wall in left
        wallStatus |= static_cast<unsigned char>(WallStatus::left);
    }

    if (leftDistance < MIN_SIDE_DISTANCE) {
        // there is the wall in right
        wallStatus |= static_cast<unsigned char>(WallStatus::right);
    }

    WallSensingEvent ev(wallStatus);

    return ev;
}
