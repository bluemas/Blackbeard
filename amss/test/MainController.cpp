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

void MainController::setWallRecognizer(WallRecognizer *wallRecognizer) {
    using namespace std::placeholders;

    mWallRecognizer = wallRecognizer;

    // Set event handler to WallRecognizer
    mWallRecognizer->addEventHandler(std::bind(&MainController::eventHandler, this, _1));
}

void MainController::eventHandler(EventBase *ev) {
    if (dynamic_cast<WallRecognizerEvent*> (ev)) {
        cout << "Collision warning!!!" << endl;
    } else {
        cerr << "Cannot find event type. Do nothing." << endl;
    }
}
