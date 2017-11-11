/*
 * Constants.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef COMMON_CONSTANTS_H_
#define COMMON_CONSTANTS_H_

enum class RobotMode {
    None,
    Manual,
    AutoPathPlanning,
    AutoMoving,
    AutoSignRecognition,
    Suspend
};

enum class Direction {
    none = 0,
    forward,
    left,
    right,
    backward,
};

enum class CamDirection {
    panleft = 0,
    panright,
    tiltup,
    tiltdown,
};

enum class SensorType {
    front = 0,
    left,
    right,
    //back
};

enum class WallStatus {
    front = 1,
    left = 2,
    right = 4,
};


enum class SignType {
    SignNone = -1,
    SignLeft = 0,
    SignRight,
    SignTurnAround,
    SignStraight,
    SignPush,
    SignStop,
    SignBall,
    SignLeft45,
    SignRight45,
    SignGo
};

#endif /* COMMON_CONSTANTS_H_ */
