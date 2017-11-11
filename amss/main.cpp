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

#include "main/MainController.h"

#include "sam/WallRecognizer.h"
#include "sam/MazeMapper.h"
#include "sam/PathPlanner.h"

#include "network/NetworkManager.h"
#include "sam/MapData.h"

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
    wallRecognizer->addWallCollisionEventHandler(mainController);
    wallRecognizer->addWallSensingEventHandler(mainController);

    // Initialize NetworkManager
    NetworkManager* networkManager = new NetworkManager();
    mainController->setNetworkManager(networkManager);

    ImageRecognizer* imageRecognizer = new ImageRecognizer();
    imageRecognizer->addLineRecogEventHandler(mainController);
    imageRecognizer->addRedDotRecogEventHandler(mainController);
    imageRecognizer->addSignRecogEventHandler(mainController);
    imageRecognizer->addSquareRecogEventHandler(mainController);

    // 4. Initiate other components
    MapData *mapRepo = new MapData();
    MazeMapper *mazeMapper = new MazeMapper(mapRepo);
    PathPlanner *pathPlanner = new PathPlanner(mapRepo);

    // 5. Make a relationship between components
    wallRecognizer->setMazeMapper(mazeMapper);
    mainController->setPathPlanner(pathPlanner);
    mainController->setImageRecognizer(imageRecognizer);

    // 5. Start threads
    wallRecognizer->start();


    // 10. Wait for stopping AMSS
    std::thread mainThread(keyInRunner);
    mainThread.join();

    cout << "AMSS is terminating..." << endl;

    // 99. Terminate instants
    wallRecognizer->stop();

    // 100. Clean up
    delete mainController;
    delete wallRecognizer;
    delete mapRepo;
    delete mazeMapper;
    delete pathPlanner;

    return 1;
}
