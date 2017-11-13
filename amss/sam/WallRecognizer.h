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
#include "../common/RecognizerBase.h"
#include "../common/event/WallCollisionEventHandler.h"
#include "../common/event/WallSensingEventHandler.h"
#include "../sensorreadloop/SensorData.h"
#include "../sensorreadloop/SonarFront.h"
#include "../sensorreadloop/FlightSensorLeft.h"
#include "../sensorreadloop/FlightSensorRight.h"

#include "MazeMapper.h"

using namespace std;

class WallRecognizer : public RecognizerBase {
public:
    WallRecognizer();
    virtual ~WallRecognizer();

    void start();
    void stop();
    void setMazeMapper(MazeMapper *mazeMapper);
    void addWallCollisionEventHandler(WallCollisionEventHandler *eventHandler);
    void addWallSensingEventHandler(WallSensingEventHandler *eventHandler);

private:
    const int SENSING_PERIOD_IN_MS = 200;

    const int MIN_FRONT_COLLISION_DISTANCE = 50;
    const int MIN_SIDE_COLLISION_DISTANCE  = 50;

    const int MIN_FRONT_WALL_DISTANCE = 100;
    const int MIN_SIDE_WALL_DISTANCE  = 100;

    std::atomic<bool> mIsRun;
    std::thread mThread;
    MazeMapper *mMazeMapper;
    vector<WallCollisionEventHandler*> mWallCollisionEventHandlers;
    vector<WallSensingEventHandler*> mWallSensingEventHandlers;
    SensorData *mSensorData;
    SonarFront *mSonarFront;
    FlightSensorLeft *mFlightSensorLeft;
    FlightSensorRight *mFlightSensorRight;

    void run();
    WallCollisionEvent checkCollision(int frontDistance, int leftDistance, int rightDistance);
    WallSensingEvent checkWallStatus(int frontDistance, int leftDistance, int rightDistance);
};

#endif /* RECOGNIZER_WALLRECOGNIZER_H_ */
