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
    return (mWallStatus & static_cast<unsigned char>(WallStatus::front)) == 1;
}

bool WallSensingEvent::isLeftWall() {
    return (mWallStatus & static_cast<unsigned char>(WallStatus::left)) == 1;
}

bool WallSensingEvent::isRightWall() {
    return (mWallStatus & static_cast<unsigned char>(WallStatus::right)) == 1;
}

void WallSensingEvent::setFrontWall() {

}

void WallSensingEvent::setLeftWall() {

}

void WallSensingEvent::setRightWall() {

}
