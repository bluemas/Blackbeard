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

//#include "../common/SensorDataRepo.h"
#include "../common/EventBase.h"

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
    const int MIN_FRONT_DISTANCE = 50;
    const int MIN_SIDE_DISTANCE  = 50;

    //SensorDataRepo *mSensorDataRepo;
    std::atomic<bool> mIsRun;
    std::thread mThread;
    std::function<void(const EventBase*)> mEventHandler;

    void run();
};

#endif /* RECOGNIZER_WALLRECOGNIZER_H_ */
