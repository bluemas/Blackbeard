/*
 * WallRecognizer.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_WALLRECOGNIZER_H_
#define SAM_WALLRECOGNIZER_H_


#include <thread>
#include <functional>

#include "../common/SensorDataRepo.h"

using namespace std;

class WallRecognizer {
public:
    WallRecognizer(SensorDataRepo *sensorDataRepo);
    virtual ~WallRecognizer();

    void init();
    void notify();
    void start();
    void stop();
    void addHandler(std::function<void(int)> callback);

private:
    const int MIN_FRONT_DISTANCE = 50;
    const int MIN_SIDE_DISTANCE  = 50;

    SensorDataRepo *mSensorDataRepo;
    bool mIsRun = true;
    std::function<void(int)> mMainControllerCallback;

    void run();
};

#endif /* RECOGNIZER_WALLRECOGNIZER_H_ */
