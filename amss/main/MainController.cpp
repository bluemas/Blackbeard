///////////////////////////////////////////////////////////
//  MainController.cpp
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "MainController.h"
#include "ManualMode.h"
#include "AutonomousPathPlanningMode.h"
#include "AutonomousMovingMode.h"
#include "AutonomousSignRecognitionMode.h"
#include "SuspendMode.h"
#include <thread>


MainController::MainController() {

}


MainController::~MainController() {

}

void MainController::start() {
    init();
    std::thread t(&MainController::runLoop, this);
    t.join();
}

void MainController::init() {
    // Create mode instances
    mModeList[RobotMode::Manual] = new ManualMode(this);
    mModeList[RobotMode::AutoPathPlanning] = new AutonomousPathPlanningMode(this);
    mModeList[RobotMode::AutoMoving] = new AutonomousMovingMode(this);
    mModeList[RobotMode::AutoSignRecognition] = new AutonomousSignRecognitionMode(this);
    mModeList[RobotMode::Suspend] = new SuspendMode(this);

    // Initialize Camera Pan/Tilt

    // Initialize maze map

}

void MainController::runLoop() {
    while (true) {

        sleep(1);
    }

}

void MainController::handleWallCollisionEvent(const WallCollisionEvent ev) {
    cout << "WallCollisionEvent!!!" << endl;
}

void MainController::handleLineRecognizedEvent(const LineRecognizedEvent ev) {
    cout << "LineRecognizedEvent!!!" << endl;
}

void MainController::handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev) {
    cout << "RedDotRecognizedEvent!!!" << endl;
}

void MainController::handleSignRecognizedEvent(const SignRecognizedEvent ev) {
    cout << "SignRecognizedEvent!!!" << endl;
}

void MainController::handleSquareRecognizedEvent(const SquareRecognizedEvent ev) {
    cout << "SquareRecognizedEvent!!!" << endl;
}

void MainController::handleMessage(int type, void* data) {
    switch (type) {
        case 1: // Initialize robot
            initializeRobot();
            break;
        case 2: // Mode Selection
        {
            auto mode = *(char*)data;
            if (mode == 'A')
                setCurrentMode(RobotMode::AutoPathPlanning);
            else if (mode == 'M')
                setCurrentMode(RobotMode::Manual);
            break;
        }
        case 3: // Move robot
            if (currentMode()->getModeName() == RobotMode::Manual)
                ((ManualMode*)currentMode())->moveRobot();
            break;
        case 4: // Adjust camera Pan/Tilt
            if (currentMode()->getModeName() == RobotMode::Manual)
                ((ManualMode*)currentMode())->adjustCamera();
            break;
        default:
            break;
    }
}

void MainController::initializeRobot() {
    // TODO : implement function which initializes robot
}

void MainController::moveRobot(const void *data) {

}

void MainController::setWallRecognizer(WallRecognizer* wallRecognizer) {
//    using namespace std::placeholders;
//
//    // Set event handler to WallRecognizer
//    wallRecognizer->addEventHandler(std::bind(
//            &MainController::wallRecognizerEventHandler,
//                                               this, std::placeholders::_1));
}

void MainController::setSignRecognizer(SignRecognizer *signRecognizer) {
    mSignRecognizer = signRecognizer;
}

void MainController::setLineRecognizer(LineRecognizer *lineRecognizer) {

}

void MainController::setDotRecognizer(DotRecognizer *dotRecognizer) {

}

void MainController::setNetworkManager(NetworkManager *networkManger) {
    mNetworkManager = networkManger;
}

PathPlanner* MainController::pathPlanner() {
    return &mPathPlanner;
}

BehaviorExecutor* MainController::behaviorExecutor() {
    return &mBehaviorExecutor;
}

void MainController::setCurrentMode(RobotMode mode) {
    mCurrentMode->doExitAction();
    mCurrentMode = mModeList[mode];
    mCurrentMode->doEntryAction();
}

NetworkManager* MainController::networkManager() {
    return mNetworkManager;
}

ModeBase* MainController::currentMode() {
    return mCurrentMode;
}
