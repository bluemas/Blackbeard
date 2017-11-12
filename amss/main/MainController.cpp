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
#include "../common/Logging.h"
#include <thread>

// TODO : Implement function sending robot status

MainController::MainController() :
    mCurrentMode(NULL) {
}

void MainController::start() {
    init();
    std::thread t(&MainController::runLoop, this);
    t.join();
}

void MainController::init() {
    // Create mode instances
    createModeInstances();

    mCurrentMode = mModeList[RobotMode::Manual];

//    initializeRobot();
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void MainController::initializeRobot() {
    // Initialize Camera Pan/Tilt
    behaviorExecutor()->setCamDefaultTrackLine();
    Logging::logOutput(Logging::INFO, "Camera position initialized");

    // Initialize maze map
    pathPlanner()->init();
    Logging::logOutput(Logging::INFO, "Maze Map initialized");

    // Set robot mode as manual
    setCurrentMode(RobotMode::Manual);
    Logging::logOutput(Logging::INFO, "Robot mode changed to Manual Mode");
}

void MainController::moveRobot(const void *data) {

}

void MainController::setCurrentMode(RobotMode mode) {
    mCurrentMode->doExitAction();

    char msg[255] = { 0 };
    snprintf(msg, 255, "Current robot mode changed to %s.",
             mode == RobotMode::Manual ? "Manual" :
             (mode == RobotMode::AutoSignRecognition ? "AutoSignRecognition" :
              (mode == RobotMode::AutoMoving ? "AutoMoving" :
               (mode == RobotMode::AutoPathPlanning ? "AutoPathPlanning" :
                (mode == RobotMode::Suspend ? "Suspend" : "Unknown")))));

    Logging::logOutput(Logging::DEBUG, msg);

    mCurrentMode = mModeList[mode];

    // Send new robot mode to RUI
    char robotMode = mCurrentMode->getModeNameChar();
    networkManager()->send(7, sizeof(char), &robotMode);

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
            else if (mode == 'S')
                setCurrentMode(RobotMode::Suspend);
            break;
        }
        case 3: // Move robot manually
            if (currentMode()->getModeName() == RobotMode::Manual) {
               ((ManualMode *)currentMode())->moveRobot(*(char*)(data));
            }
            break;
        case 4: // Adjust camera Pan/Tilt
            if (currentMode()->getModeName() == RobotMode::Manual)
                ((ManualMode*)currentMode())->adjustCamera(*(char*)(data));
            break;
        default:
            break;
    }
}