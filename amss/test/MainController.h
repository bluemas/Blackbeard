/*
 * MainController.h
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#ifndef TEST_MAINCONTROLLER_H_
#define TEST_MAINCONTROLLER_H_

#include <iostream>

#include "../common/EventBase.h"
#include "../sam/WallRecognizer.h"

using namespace std;

class MainController {
public:
    MainController();
    virtual ~MainController();

    void setWallRecognizer(WallRecognizer *wallRecognizer);
private:
    void eventHandler(EventBase *ev);

    WallRecognizer *mWallRecognizer;
};

#endif /* TEST_MAINCONTROLLER_H_ */
