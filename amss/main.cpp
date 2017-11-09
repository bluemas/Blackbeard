//int main() {
//    MainController::start();
//    NetworkManager::start();
//}
//============================================================================
// Name        : AMSS.cpp
// Author      : Black Beard
// Version     :
// Copyright   : LG
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <thread>

#include "sam/WallRecognizer.h"
#include "test/MainController.h"
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

int main()
{
    // 1. Initiate MainController
    MainController *mainController = new MainController();

    // 2. Initiate recognizers
    WallRecognizer *wallRecognizer = new WallRecognizer();

    // Initialize NetworkManager
    NetworkManager* networkManager = new NetworkManager();

    // 3. Set recognizer to main controller as a composite object
    mainController->setWallRecognizer(wallRecognizer);
    mainController->networkManager(networkManager);

    // 4. Start threads
    wallRecognizer->start();


    // 99. Wait for stopping AMSS
    std::thread mainThread(keyInRunner);
    mainThread.join();

    cout << "AMSS is terminating..." << endl;

    wallRecognizer->stop();

    return 1;
}
