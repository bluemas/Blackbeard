///////////////////////////////////////////////////////////
//  MainController.cpp
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluem
///////////////////////////////////////////////////////////

#include "MainController.h"
#include <thread>


MainController::MainController() {

}


MainController::~MainController() {

}

void MainController::start() {
    MainController* mainController = new MainController();
    mainController->init();
    std::thread t(&MainController::runLoop, mainController);
    t.join();
}

void MainController::init() {
    // TODO
    // Initialize Camera Pan/Tilt

    // Initialize maze map

}

void MainController::runLoop() {
    while (true) {

        sleep(1);
    }

}

void MainController::handleMessage(int type, void* payload) {
    switch (type) {
        case 1:
            break;
        case 2:
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