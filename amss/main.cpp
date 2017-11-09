//============================================================================
// Name        : AMSS.cpp
// Author      : Black Beard
// Version     :
// Copyright   : LG
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <wiringPi.h>

#include "test/MainController.h"

#include "sam/WallRecognizer.h"
#include "sam/MapRepo.h"
#include "sam/MazeMapper.h"
#include "sam/PathPlanner.h"

using namespace std;


void keyInRunner() {
    string command;

    while(true) {
        cout << "Press 's' to stop AMSS" << endl;
        cin >> command;

        if (command == "s") {
            break;
        }
    }
}

void init() {
    if (wiringPiSetup() == -1) {
        exit(0);
    }

    if(VL53L0X_i2c_init("/dev/i2c-1")==-1) {
        cout << "VL53L0X_i2c_init failed" << endl;
        exit(0);
    }
}

int main() {
    // 0. Initialize device
    init();

    // 1. Initiate MainController
    MainController *mainController = new MainController();

    // 2. Initiate recognizers
    WallRecognizer *wallRecognizer = new WallRecognizer();
    wallRecognizer->addEventHandler(mainController);

    // 4. Initiate other components
    MapRepo *mapRepo = new MapRepo();
    MazeMapper *mazeMapper = new MazeMapper(mapRepo);
    PathPlanner *pathPlanner = new PathPlanner(mazeMapper, mapRepo);

    // 5. Make a relationship between components
    mainController->setPathPlanner(pathPlanner);
    wallRecognizer->setMazeMapper(mazeMapper);

    // 5. Start threads
    wallRecognizer->start();


    // 10. Wait for stopping AMSS
    std::thread mainThread(keyInRunner);
    mainThread.join();

    cout << "AMSS is terminating..." << endl;

    // 99. Terminate instants
    wallRecognizer->stop();

    return 1;
}
