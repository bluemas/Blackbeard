/*
 * MainController.h
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#ifndef TEST_MAINCONTROLLER_H_
#define TEST_MAINCONTROLLER_H_

#include <iostream>

#include "../common/EventHandlerAdapter.h"
#include "../common/EventBase.h"
#include "../sam/PathPlanner.h"
#include "../sam/WallRecognizer.h"

using namespace std;

class MainController : public EventHandlerAdapter {
public:
    MainController();
    virtual ~MainController();

    void setPathPlanner(PathPlanner *pathPlanner);
    void setWallRecognizer(WallRecognizer *wallRecognizer);
private:
    PathPlanner *mPathPlanner;
    WallRecognizer *mWallRecognizer;

    void wallEventHandler(const EventBase *ev);
};

#endif /* TEST_MAINCONTROLLER_H_ */
