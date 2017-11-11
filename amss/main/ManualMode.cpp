///////////////////////////////////////////////////////////
//  ManualMode.cpp
//  Implementation of the Class ManualMode
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "ManualMode.h"
#include "MainController.h"

ManualMode::ManualMode(MainController* mainController) {
    mModeName = RobotMode::Manual;
    mMainController = mainController;
}

void ManualMode::wallEventHandler(EventBase *ev) {
    // TODO : define collision warning message(ethernet)
    mMainController->networkManager()->send(/* Collision Warning Message */);
}

void ManualMode::signRecognizerEventHandler(EventBase *ev) {
    // REVIEW : Do I need to update map to include sign into map in Manual Mode?
}

void ManualMode::moveRobot(void *data) {
    mMainController->behaviorExecutor()->manualMove(Direction::forward); // FIXME :
}

void ManualMode::adjustCamera(void *data) {
    mMainController->behaviorExecutor()->panAndTilt(CamDirection::panleft); // FIXME :
}


