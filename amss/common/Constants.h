/*
 * Constants.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef COMMON_CONSTANTS_H_
#define COMMON_CONSTANTS_H_

enum class RobotMode {
    None,    Manual,
    AutoPathPlanning,
    AutoMoving,
    AutoSignRecognition,
    Suspend
};

enum class Direction {
    forward = 0,
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
    front = 0,
    left = 1,
    right = 2,
};

#endif /* COMMON_CONSTANTS_H_ */
