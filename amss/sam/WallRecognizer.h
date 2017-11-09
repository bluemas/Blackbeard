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
#include "../common/WallRecognizerEvent.h"
#include "../common/EventHandlerAdapter.h"

#include "../sensorreadloop/SensorData.h"
#include "../sensorreadloop/SonarFront.h"
#include "../sensorreadloop/FlightSensorLeft.h"
#include "../sensorreadloop/FlightSensorRight.h"

using namespace std;

class WallRecognizer {
public:
    //WallRecognizer(SensorDataRepo *sensorDataRepo);
    WallRecognizer();
    virtual ~WallRecognizer();

    void start();
    void stop();
    void addEventHandler(EventHandlerAdapter *eventHandler);

private:
    const int SENSING_PERIOD_IN_MS = 500;
    const double MIN_FRONT_COLLISION_DISTANCE = 50;
    const double MIN_SIDE_COLLISION_DISTANCE  = 50;
    const double MIN_FRONT_DISTANCE = 50;
    const double MIN_SIDE_DISTANCE  = 50;

    //SensorDataRepo *mSensorDataRepo;
    std::atomic<bool> mIsRun;
    std::thread mThread;
    EventHandlerAdapter *mEventHandler;
    SensorData *mSensorData;
    SonarFront *mSonarFront;
    FlightSensorLeft *mFlightSensorLeft;
    FlightSensorRight *mFlightSensorRight;

    void run();
    void checkCollision(double frontDistance, double leftDistance, double rightDistance);
    void checkWall(double frontDistance, double leftDistance, double rightDistance);
};

#endif /* RECOGNIZER_WALLRECOGNIZER_H_ */
