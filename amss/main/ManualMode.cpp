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

void ManualMode::moveRobot(char direction) {
    if (direction == 'S') {
        mMainController->behaviorExecutor()->stop();
        Logging::logOutput(Logging::DEBUG, "Stop robot");
    }
    else {
        Direction newDirection = Direction::forward;
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

void ManualMode::handleCollisionEvent(WallCollisionEvent ev) {
    if (ev.isWarnCollision()) {
        char warning[256] = "E/Robot is about to hit the wall.";
        mMainController->networkManager()->send(NetworkMsg::RobotStatusMessage,
                                                strlen(warning), warning);
    }
}

void ManualMode::handleRedDotRecognizedEvent(RedDotRecognizedEvent ev) {
}

void ManualMode::handleSignRecognizedEvent(SignRecognizedEvent ev) {
}

void ManualMode::doEntryAction() {
    // Enable sign recognizer
    mMainController->imageRecognizer()->setSignRecognizeMode(true);
}

void ManualMode::doExitAction() {
    // Disable sign recognizer
    mMainController->imageRecognizer()->setSignRecognizeMode(false);
}


