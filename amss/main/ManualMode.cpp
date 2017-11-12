///////////////////////////////////////////////////////////
//  ManualMode.cpp
//  Implementation of the Class ManualMode
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "ManualMode.h"
#include "MainController.h"
#include "../common/Logging.h"

ManualMode::ManualMode(MainController* mainController) {
    mModeName = RobotMode::Manual;
    mMainController = mainController;
}

void ManualMode::wallEventHandler(EventBase *ev) {
    // TODO : define collision warning message(ethernet)
//    mMainController->networkManager()->send(/* Collision Warning Message */);
}

void ManualMode::signRecognizerEventHandler(EventBase *ev) {
    // REVIEW : Do I need to update map to include sign into map in Manual Mode?
}

void ManualMode::moveRobot(char direction) {
    if (direction == 'S') {
        mMainController->behaviorExecutor()->stop();
        Logging::logOutput(Logging::DEBUG, "Stop robot");
    }
    else {
        Direction newDirection;
        switch (direction) {
            case 'F':
                newDirection = Direction::forward;
                break;
            case 'L':
                newDirection = Direction::left;
                break;
            case 'R':
                newDirection = Direction::right;
                break;
            case 'B':
                newDirection = Direction::backward;
                break;
        }
        mMainController->behaviorExecutor()->manualMove(newDirection);
        Logging::logOutput(Logging::DEBUG, "Move robot manually");
    }
}

void ManualMode::adjustCamera(char direction) {
    if (direction == 'S') {
        mMainController->behaviorExecutor()->stopPanAndTilt();
        Logging::logOutput(Logging::DEBUG, "Stop camera pan/tilt");
    }
    else {
        CamDirection newDirection;
        switch (direction) {
            case 'L':
                newDirection = CamDirection::panleft;
                break;
            case 'R':
                newDirection = CamDirection::panright;
                break;
            case 'U':
                newDirection = CamDirection::tiltup;
                break;
            case 'D':
                newDirection = CamDirection::tiltdown;
                break;
        }
        mMainController->behaviorExecutor()->panAndTilt(newDirection);
        Logging::logOutput(Logging::DEBUG, "Adjust Camera Pan/Tilt");
    }
}


