/*
 * Constants.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef COMMON_CONSTANTS_H_
#define COMMON_CONSTANTS_H_

enum Direction {
	none = -1,
    forward = 0,
    left,
    right,
    backward
};

enum class RobotMode {
    None,
	Manual,
	AutoPathPlanning,
	AutoMoving,
	AutoSignRecognition,
	Suspend
};

#endif /* COMMON_CONSTANTS_H_ */
