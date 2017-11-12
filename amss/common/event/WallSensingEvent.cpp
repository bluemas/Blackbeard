/*
 * WallSensingEvent.cpp
 *
 *  Created on: 2017. 11. 8.
 *      Author: gtlove
 */

#include "WallSensingEvent.h"

WallSensingEvent::WallSensingEvent() {
    mWallStatus = 0;
}

WallSensingEvent::~WallSensingEvent() {

}

unsigned char WallSensingEvent::getWallStatus() {
    return mWallStatus;
}

bool WallSensingEvent::isFrontWall() {
    return (mWallStatus & 1) == 1;
}

bool WallSensingEvent::isLeftWall() {
    return (mWallStatus & 2) == 2;
}

bool WallSensingEvent::isRightWall() {
    return (mWallStatus & 4) == 4;
}

void WallSensingEvent::setFrontWall() {
    mWallStatus |= 1;
}

void WallSensingEvent::setLeftWall() {
    mWallStatus |= 2;
}

void WallSensingEvent::setRightWall() {
    mWallStatus |= 4;
}
