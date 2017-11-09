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
#include "../common/event/WallCollisionEvent.h"
#include "../sam/PathPlanner.h"
#include "../sam/WallRecognizer.h"
#include "../network/NetworkManager.h"

using namespace std;

class MainController : public EventHandlerAdapter {
public:
    MainController();
    virtual ~MainController();

    void setWallRecognizer(WallRecognizer *wallRecognizer);
    void setPathPlanner(PathPlanner *pathPlanner);
    void setNetworkManager(NetworkManager *networkManager);

    void handleWallCollisionEvent(const WallCollisionEvent ev);
    void handleLineRecognizedEvent(const LineRecognizedEvent ev);
    void handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev);
    void handleSignRecognizedEvent(const SignRecognizedEvent ev);
    void handleSquareRecognizedEvent(const SquareRecognizedEvent ev);
private:
    PathPlanner *mPathPlanner;
    WallRecognizer *mWallRecognizer;

};

#endif /* TEST_MAINCONTROLLER_H_ */
