/*
 * WallSensingEvent.cpp
 *
 *  Created on: 2017. 11. 8.
 *      Author: gtlove
 */

#include "WallSensingEvent.h"

WallSensingEvent::WallSensingEvent(unsigned char wallStatus) {
    mWallStatus = wallStatus;
}

WallSensingEvent::~WallSensingEvent() {

}

bool WallSensingEvent::isFrontWall() {
    return (mWallStatus & WallStatus::front) == 1;
}

bool WallSensingEvent::isLeftWall() {
    return (mWallStatus & WallStatus::left) == 1;
}

bool WallSensingEvent::isRightWall() {
    return (mWallStatus & WallStatus::right) == 1;
}
