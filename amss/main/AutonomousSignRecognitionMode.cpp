//
// Created by lg on 11/7/17.
//

#include "AutonomousSignRecognitionMode.h"
#include "../common/EventBase.h"

AutonomousSignRecognitionMode::AutonomousSignRecognitionMode(MainController* mainController) {
    mModeName = RobotMode::AutoSignRecognition;
    mMainController = mainController;
    mSignFound = false;
}

void AutonomousSignRecognitionMode::doEntryAction() {
    // Start sign recognizer
    mMainController->signRecognizer()->start();

    // TODO : Determine how wall information can be retrieved and call following
    // functions as necessary
    // Search sign on left wall
    mMainController->behaviorExecutor()->searchSign(Direction::left);

    // Search sign on front wall
    if (!mSignFound) {
        mMainController->behaviorExecutor()->searchSign(Direction::forward);
    }

    // Search sign on right wall
    if (!mSignFound)
        mMainController->behaviorExecutor()->searchSign(Direction::right);

    // If sign is not found, transition to suspend mode
    if (!mSignFound)
        mMainController->setCurrentMode(RobotMode::Suspend);
}

void AutonomousSignRecognitionMode::signRecognizerEventHandler(EventBase *ev) {
    mSignFound = true;

    // Stop sign recognizer
    mMainController->signRecognizer()->stop();

    // Adjust camera pan/tilt to default angle for line following
    mMainController->behaviorExecutor()->setCamDefaultTrackLine();

    // Transition to Autonomous Path Planning Mode
    mMainController->setCurrentMode(RobotMode::AutoPathPlanning);
}