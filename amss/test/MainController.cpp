/*
 * MainController.cpp
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#include "MainController.h"

MainController::MainController() {

}

MainController::~MainController() {

}

void MainController::setPathPlanner(PathPlanner *pathPlanner) {
    mPathPlanner = pathPlanner;
}

void MainController::setWallRecognizer(WallRecognizer *wallRecognizer) {
    using namespace std::placeholders;

    mWallRecognizer = wallRecognizer;

    // Set event handler to WallRecognizer
    mWallRecognizer->addEventHandler(std::bind(&MainController::wallEventHandler, this, _1));
}

void MainController::wallEventHandler(const EventBase *ev) {
    cout << "Collision warning!!!" << endl;
}
