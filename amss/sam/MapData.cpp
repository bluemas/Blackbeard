/*
 * MapData.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MapData.h"


MapData::MapData() {

}


MapData::~MapData() {

}

void MapData::init() {
    // TODO init MapRepo
    mFirstGrid = true;
}

void MapData::setNextDirection(Direction dir) {
    mNextDirection = dir;
}

Direction MapData::getNextDirection() {
    return mNextDirection;
}

MazeGrid MapData::getCurrMazeGrid() {
    return mMazeArr[mPosX][mPosY];
}

void MapData::setCurrMazeGrid(MazeGrid grid) {
    MazeGrid curGrid = mMazeArr[mPosX][mPosY];
    // TODO Merge grid info
}
void MapData::setFrontMazeGrid(MazeGrid newNextGrid) {
    int nextPosX = mPosX, nextPosY = mPosY;

    if (mRobotDirection == Direction::forward) {
        nextPosY++;
    } else if (mRobotDirection == Direction::backward) {
        nextPosY--;
    } else if (mRobotDirection == Direction::left) {
        nextPosX--;
    } else if (mRobotDirection == Direction::right) {
        nextPosX++;
    }

    MazeGrid oldNextGrid = mMazeArr[nextPosX][nextPosY];

    mergeGrid(oldNextGrid, newNextGrid);
}

void MapData::printMap() {

}

bool MapData::isFirstGrid() {
    return mPosY == 0 && mPosX == 0;
}

void MapData::mergeGrid(MazeGrid g1, MazeGrid g2) {

}

