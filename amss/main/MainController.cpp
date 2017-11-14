///////////////////////////////////////////////////////////
//  MainController.cpp
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "MainController.h"
#include "AutonomousMovingMode.h"
#include "AutonomousSignRecognitionMode.h"
#include "SuspendMode.h"
#include "../common/Logging.h"
#include "../sensorreadloop/SensorData.h"

MainController::MainController() :
    mCurrentMode(NULL),
    mConnected(false) {
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
}

void MainController::createModeInstances()  {
    mModeList[RobotMode::Manual] = new ManualMode(this);
    mModeList[RobotMode::AutoPathPlanning] = new AutonomousPathPlanningMode(this);
    mModeList[RobotMode::AutoMoving] = new AutonomousMovingMode(this);
    mModeList[RobotMode::AutoSignRecognition] = new AutonomousSignRecognitionMode(this);
    mModeList[RobotMode::Suspend] = new SuspendMode(this);
}

void MainController::runLoop() {
    bool bRun = true;
    while (bRun) {
        // Send sensor data to RUI
        if (mConnected) {
            sendSensorData();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void MainController::sendSensorData() {
    SensorData* sensorData = SensorData::getInstance();

    int leftDistance = sensorData->getData(SensorType::left);
    int frontDistance = sensorData->getData(SensorType::front);
    int rightDistance = sensorData->getData(SensorType::right);

    char distances[100] = { 0 };
    snprintf(distances, 100, "%d/%d/%d",
             leftDistance, frontDistance, rightDistance);
    networkManager()->send(NetworkMsg::SensorData, strlen(distances), distances);
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

    // Send new robot mode to RUI
    char robotMode = mCurrentMode->getModeNameChar();
    networkManager()->send(NetworkMsg::RobotMode, sizeof(char), &robotMode);

    Logging::logOutput(Logging::INFO, "Robot mode changed to Manual Mode");

    // Send robot initialization status to RUI
    networkManager()->send(NetworkMsg::RobotInitialized, 0, NULL);
}

void MainController::setCurrentMode(RobotMode mode) {
    if (mode == mCurrentMode->getModeName())
        return;

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
    networkManager()->send(NetworkMsg::RobotMode, sizeof(char), &robotMode);

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

void MainController::handleCrossRecognizedEvent(const CrossRecognizedEvent ev) {
    Logging::logOutput(Logging::INFO, "CROSS RECOGNIZED");
    currentMode()->handleCrossRecognizedEvent(ev);
}

void MainController::handleMessage(NetworkMsg type, void* data) {
    switch (type) {
        case NetworkMsg::Initialize: // Initialize robot
            initializeRobot();
            break;
        case NetworkMsg::ChangeMode: // Mode Selection
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
        case NetworkMsg::MoveRobot: // Move robot manually
            if (currentMode()->getModeName() == RobotMode::Manual) {
               ((ManualMode *)currentMode())->moveRobot(*(char*)(data));
            }
            break;
        case NetworkMsg::AdjustCameraPanTilt: // Adjust camera Pan/Tilt
            if (currentMode()->getModeName() == RobotMode::Manual)
                ((ManualMode*)currentMode())->adjustCamera(*(char*)(data));
            break;
        case NetworkMsg::NetworkConnection: // Network connection
            mConnected = true;
            break;
        case NetworkMsg::NetworkDisconnection: // Network disconnection
            mConnected = false;
            break;
        default:
            break;
    }
}
