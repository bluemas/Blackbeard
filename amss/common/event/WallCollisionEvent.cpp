/*
 * WallRecognizerEvent.cpp
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#include "WallCollisionEvent.h"

WallCollisionEvent::WallCollisionEvent() {

}

WallCollisionEvent::~WallCollisionEvent() {

}

bool WallCollisionEvent::isWarnCollision() {
    return mFrontDistance != -1 || mLeftDistance != -1 || mRightDistance != -1;
}

int WallCollisionEvent::getFrontDistance() {
    return mFrontDistance;
}

int WallCollisionEvent::getLeftDistance() {
    return mFrontDistance;
}

int WallCollisionEvent::getRightDistance() {
    return mFrontDistance;
}

void WallCollisionEvent::setFrontDistance(int val) {
    mFrontDistance = val;
}

void WallCollisionEvent::setLeftDistance(int val) {
    mLeftDistance = val;
}

void WallCollisionEvent::setRightDistance(int val) {
    mRightDistance = val;
}
