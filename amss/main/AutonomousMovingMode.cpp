///////////////////////////////////////////////////////////
//  AutonomousPathMovingMode.cpp
//  Implementation of the Class AutonomousPathMovingMode
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "AutonomousMovingMode.h"
#include "MainController.h"

AutonomousMovingMode::AutonomousMovingMode(
        MainController* mainController) :
    mModeName(RobotMode::AutoMoving),
    mMainController(mainController) {
}

void AutonomousMovingMode::handleCollisionEvent(WallCollisionEvent ev) {
    // TODO : define collision warning message(ethernet)
    if (ev.isWarnCollision())
        mMainController->networkManager()->send(/* Collision Warning Message */);
}

void AutonomousMovingMode::handleWallSensingEvent(WallSensingEvent ev) {
    // TODO : Do I need to implement this handler in Moving Mode?
}

void AutonomousMovingMode::handleLineRecognizedEvent(LineRecognizedEvent ev) {
    mMainController->behaviorExecutor()->setOffset(ev.getOffset());
}

void AutonomousMovingMode::handleRedDotRecognizedEvent(
        RedDotRecognizedEvent ev) {
    mMainController->behaviorExecutor()->gotoCross();
    mMainController->setCurrentMode(RobotMode::AutoSignRecognition);
}