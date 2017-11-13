///////////////////////////////////////////////////////////
//  AutonomousPathMovingMode.cpp
//  Implementation of the Class AutonomousPathMovingMode
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "AutonomousMovingMode.h"
#include "MainController.h"

AutonomousMovingMode::AutonomousMovingMode(MainController* mainController) {
     mMainController = mainController;
     mModeName = RobotMode::AutoMoving;
}

void AutonomousMovingMode::handleCollisionEvent(WallCollisionEvent ev) {
    if (ev.isWarnCollision()) {
        char warning[256] = "E/Robot is about to hit the wall.";
        mMainController->networkManager()->send(NetworkMsg::RobotStatusMessage, 
                                                strlen(warning), warning);
    }
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

void AutonomousMovingMode::handleCrossRecognizedEvent(CrossRecognizedEvent ev) {
    mMainController->setCurrentMode(RobotMode::AutoPathPlanning);
}

void AutonomousMovingMode::doEntryAction() {
    mMainController->imageRecognizer()->setLineRecognizeMode(true);
}

void AutonomousMovingMode::doExitAction() {
    mMainController->imageRecognizer()->setLineRecognizeMode(false);
}
