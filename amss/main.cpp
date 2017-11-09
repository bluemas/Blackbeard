//============================================================================
// Name        : AMSS.cpp
// Author      : Black Beard
// Version     :
// Copyright   : LG
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <thread>

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

int main()
{
    // 1. Initiate MainController
    MainController *mainController = new MainController();

    // 2. Initiate recognizers
    WallRecognizer *wallRecognizer = new WallRecognizer();
    wallRecognizer->addEventHandler(mainController);

    // 4. Initiate other components
    MapRepo *mapRepo = new MapRepo();
    MazeMapper *mazeMapper = new MazeMapper(mapRepo);
    PathPlanner *pathPlanner = new PathPlanner(mazeMapper, mapRepo);

    // 5. Set other components to main controller
    mainController->setPathPlanner(pathPlanner);

    // 5. Start threads
    wallRecognizer->start();


    // 99. Wait for stopping AMSS
    std::thread mainThread(keyInRunner);
    mainThread.join();

    cout << "AMSS is terminating..." << endl;

    wallRecognizer->stop();

    return 1;
}
