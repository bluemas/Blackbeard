/*
 * WallRecognizer.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_WALLRECOGNIZER_H_
#define SAM_WALLRECOGNIZER_H_


#include <future>
#include <atomic>
#include <thread>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

#include "../common/Constants.h"
#include "../common/EventBase.h"
//#include "../common/SensorDataRepo.h"

#include "WallRecognizerEvent.h"

using namespace std;

class WallRecognizer {
public:
    //WallRecognizer(SensorDataRepo *sensorDataRepo);
    WallRecognizer();
    virtual ~WallRecognizer();

    void start();
    void stop();
    void addEventHandler(std::function<void(const EventBase*)> eventHandler);

private:
    const int SENSING_PERIOD_IN_MS = 100;
    const double MIN_FRONT_COLLISION_DISTANCE = 40;
    const double MIN_SIDE_COLLISION_DISTANCE  = 40;
    const double MIN_FRONT_DISTANCE = 50;
    const double MIN_SIDE_DISTANCE  = 50;

    //SensorDataRepo *mSensorDataRepo;
    std::atomic<bool> mIsRun;
    std::thread mThread;
    std::function<void(const EventBase*)> mEventHandler;

    void run();
    void checkCollision(double frontDistance, double leftDistance, double rightDistance);
    void checkWall(double frontDistance, double leftDistance, double rightDistance);
};

#endif /* RECOGNIZER_WALLRECOGNIZER_H_ */
