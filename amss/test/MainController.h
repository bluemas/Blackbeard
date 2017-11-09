/*
 * MainController.h
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#ifndef TEST_MAINCONTROLLER_H_
#define TEST_MAINCONTROLLER_H_

#include <iostream>

#include "../common/event/EventHandlerAdapter.h"
#include "../common/event/WallRecognizerEvent.h"
#include "../sam/PathPlanner.h"
#include "../sam/WallRecognizer.h"

using namespace std;

class MainController : public EventHandlerAdapter {
public:
    MainController();
    virtual ~MainController();

    void setPathPlanner(PathPlanner *pathPlanner);
    void wallEventHandler(const WallRecognizerEvent *ev);
private:
    PathPlanner *mPathPlanner;
    WallRecognizer *mWallRecognizer;

};

#endif /* TEST_MAINCONTROLLER_H_ */
