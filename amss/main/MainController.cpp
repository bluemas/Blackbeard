///////////////////////////////////////////////////////////
//  MainController.cpp
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluem
///////////////////////////////////////////////////////////

#include "MainController.h"
#include "ManualMode.h"
#include "AutonomousPathPlanningMode.h"
#include "AutonomousMovingMode.h"
#include "AutonomouseSignRecognitionMode.h"
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
    // TODO
    // Create mode instances
    mModeList.add(new ManualMode());
    mModeList.push_back(new AutonomousPathPlanningMode());
    mModeList.push_back(new AutonomousMovingMode());
    mModeList.push_back(new AutonomouseSignRecognitionMode());
    mModeList.push_back(new SuspendMode());

    // Initialize Camera Pan/Tilt

    // Initialize maze map

}


void MainController::setWallRecognizer(WallRecognizer* wallRecognizer) {
    using namespace std::placeholders;

    mWallRecognizer = wallRecognizer;

    // Set event handler to WallRecognizer
    mWallRecognizer->addEventHandler(std::bind(&MainController::eventHandler,
                                               this, _1));
}

void MainController::eventHandler(EventBase *ev) {
    if (dynamic_cast<WallRecognizerEvent*> (ev)) {
        cout << "Collision warning!!!" << endl;
    } else {
        cerr << "Cannot find event type. Do nothing." << endl;
    }
}

void MainController::runLoop() {
    while (true) {

        sleep(1);
    }

}

void MainController::handleMessage(int type, void* data) {
    switch (type) {
        case 1:
            break;
        case 2: // Mode Selection
            char mode = *(char*)data;
            if (mode == 'A')
                mCurrentMode =
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            break;
    }
}