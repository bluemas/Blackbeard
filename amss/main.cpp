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

    // 3. Set recognizer to main controller as a composite object
    mainController->setWallRecognizer(wallRecognizer);

    // 4. Start threads
    wallRecognizer->start();


    // 99. Wait for stopping AMSS
    std::thread mainThread(keyInRunner);
    mainThread.join();

    cout << "AMSS is terminating..." << endl;

    return 1;
}
