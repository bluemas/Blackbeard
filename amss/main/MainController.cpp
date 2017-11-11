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
#include "../camera/ImageRecognizer.h"
#include <thread>


MainController::MainController() :
    mCurrentMode(NULL) {
}

MainController::~MainController() {}

void MainController::start() {
    initDevices();
    std::thread t(&MainController::runLoop, this);
    t.join();
}

void MainController::initDevices() {
    // Create mode instances
    createModeInstances();

    mCurrentMode = mModeList[RobotMode::Manual];

    // Initialize Camera Pan/Tilt
    behaviorExecutor()->setCamDefaultTrackLine();

    // Initialize maze map
    pathPlanner()->init();
}

void MainController::createModeInstances()  {
    mModeList[RobotMode::Manual] = new ManualMode(this);
    mModeList[RobotMode::AutoPathPlanning] = new AutonomousPathPlanningMode(this);
    mModeList[RobotMode::AutoMoving] = new AutonomousMovingMode(this);
    mModeList[RobotMode::AutoSignRecognition] = new AutonomousSignRecognitionMode(this);
    mModeList[RobotMode::Suspend] = new SuspendMode(this);
}

void MainController::runLoop() {
    while (true) {

        sleep(1);
    }

}

void MainController::initializeRobot() {
    // TODO : implement function which initializes robot
}

void MainController::moveRobot(const void *data) {

}

void MainController::setCurrentMode(RobotMode mode) {
    mCurrentMode->doExitAction();
    mCurrentMode = mModeList[mode];
    mCurrentMode->doEntryAction();
}

void MainController::setImageRecognizer(ImageRecognizer* imageRecognizer) {
    mImageRecognizer = imageRecognizer;
}

void MainController::setNetworkManager(NetworkManager *networkManger) {
    mNetworkManager = networkManger;
}

void MainController::setPathPlanner(PathPlanner *pathPlanner) {
    mPathPlanner = pathPlanner;
}

PathPlanner* MainController::pathPlanner() {
    return mPathPlanner;
}

BehaviorExecutor* MainController::behaviorExecutor() {
    return &mBehaviorExecutor;
}

NetworkManager* MainController::networkManager() {
    return mNetworkManager;
}

ImageRecognizer *MainController::imageRecognizer() {
    return mImageRecognizer;
}

ModeBase* MainController::currentMode() {
    return mCurrentMode;
}

void MainController::handleWallSensingEvent(const WallSensingEvent ev) {
    currentMode()->handleWallSensingEvent(ev);
}

void MainController::handleWallCollisionEvent(const WallCollisionEvent ev) {
    currentMode()->handleWallCollisionEvent(ev);
}

void MainController::handleLineRecognizedEvent(const LineRecognizedEvent ev) {
    currentMode()->handleLineRecognizedEvent(ev);
}

void MainController::handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev) {
    currentMode()->handleRedDotRecognizedEvent(ev);
}

void MainController::handleSignRecognizedEvent(const SignRecognizedEvent ev) {
    currentMode()->handleSignRecognizedEvent(ev);
}

void MainController::handleSquareRecognizedEvent(const SquareRecognizedEvent ev) {
    currentMode()->handleSquareRecognizedEvent(ev);
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
                ((ManualMode*)currentMode())->moveRobot(NULL);  // FIXME : Need to modify parameter
            break;
        case 4: // Adjust camera Pan/Tilt
            if (currentMode()->getModeName() == RobotMode::Manual)
                ((ManualMode*)currentMode())->adjustCamera(NULL);     // FIXME : Need to modify parameter
            break;
        default:
            break;
    }
}