/*
 * MazeGrid.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/MazeGrid.h"

MazeGrid::MazeGrid() {

}

MazeGrid::~MazeGrid() {

}

void MazeGrid::init() {
    mVisited = false;
    mForwardWall = false;
    mBackwardWall = false;
    mLeftWall = false;
    mRightWall = false;
    mRedDotFound = false;
    mSignType = SignType::SignNone;
    mSignDirection = Direction::none;
    mEndSqureFound = false;
}

void MazeGrid::setForwardWall(bool isWall) {
    mForwardWall = isWall;
}

void MazeGrid::setBackwardWall(bool isWall) {
    mBackwardWall = isWall;
}

void MazeGrid::setLeftWall(bool isWall) {
    mLeftWall = isWall;
}

void MazeGrid::setRightWall(bool isWall) {
    mRightWall = isWall;
}

bool MazeGrid::isForwardWall() {
    return mForwardWall;
}

bool MazeGrid::isBackwardWall() {
    return mBackwardWall;
}

bool MazeGrid::isLeftWall() {
    return mLeftWall;
}

bool MazeGrid::isRightWall() {
    return mRightWall;
}

void MazeGrid::setVisited() {

}

void MazeGrid::setRedDot() {
    mRedDotFound = true;
}

void MazeGrid::setSign(SignType signType, Direction dir) {
    mSignType = signType;
    mSignDirection = dir;
}

void MazeGrid::setStartSquare() {
    mStartSqureFound = true;
}

void MazeGrid::setEndSquare() {
    mEndSqureFound = true;
}

bool MazeGrid::isVisited() {
    return mVisited;
}

bool MazeGrid::isRedDot() {
    return mRedDotFound;
}

bool MazeGrid::isStartSquare() {
    return mStartSqureFound;
}

bool MazeGrid::isEndSquare() {
    return mEndSqureFound;
}

SignType MazeGrid::getSignType() {
    return mSignType;
}

Direction MazeGrid::getSignDirection() {
    return mSignDirection;
}
