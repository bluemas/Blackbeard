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
#include "servoencoder/BehaviorExecutor.h"
#include "sam/WallRecognizer.h"
#include "sam/MazeMapper.h"
#include "sam/PathPlanner.h"
#include "network/NetworkManager.h"

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

void initDevices() {
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
    #ifndef UBUNTU
    initDevices();
    #endif

    // 1. Initiate MainController
    MainController *mainController = new MainController();


    // 2. Initiate recognizers
    WallRecognizer *wallRecognizer = new WallRecognizer();
    ImageRecognizer* imageRecognizer = new ImageRecognizer();


    // 3. Initiate other components
    BehaviorExecutor *behaviorExecutor = new BehaviorExecutor();
    behaviorExecutor->setCamDefaultTrackLine();

    NetworkManager* networkManager = new NetworkManager();
    networkManager->addListener(mainController);

    MazeMapper *mazeMapper = new MazeMapper();
    PathPlanner *pathPlanner = new PathPlanner();


    // 4. Make a relationship between components
    mainController->setNetworkManager(networkManager);
    mainController->setPathPlanner(pathPlanner);
    mainController->setImageRecognizer(imageRecognizer);

    wallRecognizer->setMazeMapper(mazeMapper);
    wallRecognizer->addWallCollisionEventHandler(mainController);
    wallRecognizer->addWallSensingEventHandler(mainController);
    wallRecognizer->addWallSensingEventHandler(mazeMapper);

    imageRecognizer->addLineRecogEventHandler(mainController);
    imageRecognizer->addCrossRecogEventHandler(mainController);
    imageRecognizer->addCrossRecogEventHandler(mazeMapper);
    imageRecognizer->addRedDotRecogEventHandler(mainController);
    imageRecognizer->addRedDotRecogEventHandler(mazeMapper);
    imageRecognizer->addSignRecogEventHandler(mainController);
    imageRecognizer->addSignRecogEventHandler(mazeMapper);
    imageRecognizer->addSquareRecogEventHandler(mainController);
    imageRecognizer->addSquareRecogEventHandler(mazeMapper);


    // 5. Start threads
    networkManager->start();
    wallRecognizer->start();

    #ifndef UBUNTU
    imageRecognizer->start();
    #endif

    mainController->start();


    // 6. Wait for stopping AMSS
    std::thread mainThread(keyInRunner);
    mainThread.join();

    cout << "AMSS is terminating..." << endl;


    // 99. Terminate instants
    imageRecognizer->stop();
    wallRecognizer->stop();


    // 100. Clean up
    //delete mainController;
    delete imageRecognizer;
    delete wallRecognizer;
    delete mazeMapper;
    delete pathPlanner;

    return 1;
}
