///////////////////////////////////////////////////////////
//  AutonomousPathMovingMode.cpp
//  Implementation of the Class AutonomousPathMovingMode
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "AutonomousMovingMode.h"
#include "MainController.h"

AutonomousMovingMode::AutonomousMovingMode(MainController* mainController) {
    mModeName = RobotMode::AutoMoving;
    mMainController = mainController;
}

void AutonomousMovingMode::lineRecognizerEventHandler(EventBase *ev) {
    // TODO : define Event Handler Parameter
    mMainController->behaviorExecutor()->setOffset(0.0);
}

void AutonomousMovingMode::redDotRecognizerEventHandler(EventBase *ev) {
    mMainController->behaviorExecutor()->gotoCross();
    mMainController->setCurrentMode(RobotMode::AutoSignRecognition);
}

void AutonomousMovingMode::squareRecognizerEventHandler(EventBase *ev) {
    // TODO : Do I need to update map to include sign into map?
    // Or SquareRecognizer will update map?
}

void AutonomousMovingMode::wallEventHandler(EventBase *ev) {
    // TODO : define collision warning message(ethernet)
    mMainController->networkManager()->send(/* Collision Warning Message */);
}

