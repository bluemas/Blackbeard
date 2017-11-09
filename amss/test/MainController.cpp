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
