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

    mMazeArr[mPosX][mPosY] = 'S';
}

void MapData::setNextDirection(Direction dir) {
    mNextDirection = dir;

    if (dir == Direction::forward) {
        if      (mRobotDirection == Direction::forward)     { mPosY -= 1; mRobotDirection = Direction::forward; }// forward
        else if (mRobotDirection == Direction::left)        { mPosX -= 1; mRobotDirection = Direction::left; }// left
        else if (mRobotDirection == Direction::right)       { mPosX += 1; mRobotDirection = Direction::right; }// right
        else if (mRobotDirection == Direction::backward)    { mPosY += 1; mRobotDirection = Direction::backward; }// backward
    } else if (dir == Direction::left) {
        if      (mRobotDirection == Direction::forward)     { mPosX -= 1; mRobotDirection = Direction::left; } // left
        else if (mRobotDirection == Direction::left)        { mPosY += 1; mRobotDirection = Direction::backward; } // backward
        else if (mRobotDirection == Direction::right)       { mPosY -= 1; mRobotDirection = Direction::forward; } // forward
        else if (mRobotDirection == Direction::backward)    { mPosX += 1; mRobotDirection = Direction::right; } // right
    } else if (dir == Direction::right) {
        if      (mRobotDirection == Direction::forward)     { mPosX += 1; mRobotDirection = Direction::right; } // right
        else if (mRobotDirection == Direction::left)        { mPosY -= 1; mRobotDirection = Direction::forward; } // forward
        else if (mRobotDirection == Direction::right)       { mPosY += 1; mRobotDirection = Direction::backward; } // backward
        else if (mRobotDirection == Direction::backward)    { mPosX -= 1; mRobotDirection = Direction::left; } // left
    } else if (dir == Direction::backward) {
        if      (mRobotDirection == Direction::forward)     { mPosY += 1; mRobotDirection = Direction::backward; } // backward
        else if (mRobotDirection == Direction::left)        { mPosX += 1; mRobotDirection = Direction::right; } // right
        else if (mRobotDirection == Direction::right)       { mPosX -= 1; mRobotDirection = Direction::left; } // left
        else if (mRobotDirection == Direction::backward)    { mPosY -= 1; mRobotDirection = Direction::forward; } // forward
    }
}

Direction MapData::getNextDirection() {
    return mNextDirection;
}

void MapData::setMazeStatus(char front, char left, char right, char floor) {
    // If the direction of robot is front.
    if (mRobotDirection == Direction::forward) {
        if (front != '\0')  mMazeArr[mPosX][mPosY - 1] = front;
        if (left  != '\0')  mMazeArr[mPosX - 1][mPosY] = left;
        if (right != '\0')  mMazeArr[mPosX + 1][mPosY] = right;
    } else if (mRobotDirection == Direction::backward) {
        if (front != '\0')  mMazeArr[mPosX][mPosY + 1] = front;
        if (left  != '\0')  mMazeArr[mPosX + 1][mPosY] = left;
        if (right != '\0')  mMazeArr[mPosX - 1][mPosY] = right;
    } else if (mRobotDirection == Direction::left) {
        if (front != '\0')  mMazeArr[mPosX - 1][mPosY] = front;
        if (left  != '\0')  mMazeArr[mPosX][mPosY + 1] = left;
        if (right != '\0')  mMazeArr[mPosX][mPosY - 1] = right;
    } else if (mRobotDirection == Direction::right) {
        if (front != '\0')  mMazeArr[mPosX - 1][mPosY] = front;
        if (left  != '\0')  mMazeArr[mPosX][mPosY + 1] = left;
        if (right != '\0')  mMazeArr[mPosX][mPosY - 1] = right;
    }

    if (floor != '\0') {
        mMazeArr[mPosX][mPosY] = floor;
    }
}

/*
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
*/

void MapData::printMap() {
    for(int inx = 0; inx < MAZE_SIZE; inx++) {
        for(int jnx = 0; jnx < MAZE_SIZE; jnx++) {
            if (mPosX == jnx && mPosY == inx)
                cout << 'C';
            else
                cout << (mMazeArr[jnx][inx] == '\0' ? ' ' : mMazeArr[jnx][inx]);
        }

        cout << endl;
    }
    cout << "12345678901234567890" << endl;
}

bool MapData::isFirstGrid() {
    return mPosY == 10 && mPosX == 10;
}


