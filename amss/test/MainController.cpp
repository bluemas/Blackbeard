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

void MainController::wallEventHandler(const WallRecognizerEvent *ev) {
    cout << "Collision warning!!!" << endl;
}
