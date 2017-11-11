//
// Created by lg on 11/7/17.
//

#include "AutonomousSignRecognitionMode.h"
#include "../common/event/EventBase.h"
#include "MainController.h"

AutonomousSignRecognitionMode::AutonomousSignRecognitionMode(
        MainController* mainController) :
    mLeftWallDetected(false),
    mFrontWallDetected(false),
    mRightWallDetected(false),
    mModeName(RobotMode::AutoSignRecognition),
    mMainController(mainController),
    mSignFound(false) {
}

void AutonomousSignRecognitionMode::doEntryAction() {
    // Start sign recognizer
    // REVIEW : Sign Recognizer만 Start/Stop 할 수 있는 기능 필요(정윤식)
    mMainController->imageRecognizer()->start();

    // Search sign on left wall
    if (mLeftWallDetected)
        mMainController->behaviorExecutor()->searchSign(Direction::left);

    // Search sign on front wall
    if (!mSignFound && mFrontWallDetected) {
        mMainController->behaviorExecutor()->searchSign(Direction::forward);
    }

    // Search sign on right wall
    if (!mSignFound && mRightWallDetected)
        mMainController->behaviorExecutor()->searchSign(Direction::right);

    // If sign is not found, transition to suspend mode
    if (!mSignFound)
        mMainController->setCurrentMode(RobotMode::Suspend);
}

void AutonomousSignRecognitionMode::handleSignRecognizedEvent(
        const SignRecognizedEvent ev) {
    mSignFound = true;

    // Stop sign recognizer
    mMainController->imageRecognizer()->stop();

    // Stop adjusting camera pan/tilt for sign searching
    mMainController->behaviorExecutor()->stopSign();

    // Transition to Autonomous Path Planning Mode
    mMainController->setCurrentMode(RobotMode::AutoPathPlanning);
}

void AutonomousSignRecognitionMode::handleWallSensingEvent(
        const WallSensingEvent ev) {
    mLeftWallDetected = ev.isLeftWall();
    mFrontWallDetected = ev.isFrontWall();
    mRightWallDetected = ev.isRightWall();
}
