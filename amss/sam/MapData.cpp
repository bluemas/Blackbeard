/*
 * MapData.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MapData.h"

MapData *MapData::sInstance;

MapData::MapData() {

}

MapData::~MapData() {

}

MapData* MapData::getInstance() {
    if(sInstance == NULL) {
        sInstance = new MapData();
    }

    return sInstance;
}

void MapData::init() {
    // Initialize map data
    for(int inx = 0; inx < MAZE_SIZE; inx++) {
        for(int jnx = 0; jnx < MAZE_SIZE; jnx++) {
            mMazeArr[jnx][inx].init();
        }
    }

    // Initialize robot position
    mFirstGrid = true;

    mPosX = mPosY = mMinX = mMinY = mMaxX = mMaxY = INIT_POSITION;

    mMazeArr[mPosX][mPosY].setStartSquare();

    mRobotDirection = Direction::forward;
    mNextDirection = Direction::forward;
    mIsBackTracking = false;
}

void MapData::setNextDirection(Direction dir) {
    mNextDirection = dir;

    if (dir == Direction::forward) {
        if      (mRobotDirection == Direction::forward)     { mPosY -= 1; mRobotDirection = Direction::forward; }
        else if (mRobotDirection == Direction::left)        { mPosX -= 1; mRobotDirection = Direction::left; }
        else if (mRobotDirection == Direction::right)       { mPosX += 1; mRobotDirection = Direction::right; }
        else if (mRobotDirection == Direction::backward)    { mPosY += 1; mRobotDirection = Direction::backward; }
    } else if (dir == Direction::left) {
        if      (mRobotDirection == Direction::forward)     { mPosX -= 1; mRobotDirection = Direction::left; }
        else if (mRobotDirection == Direction::left)        { mPosY += 1; mRobotDirection = Direction::backward; }
        else if (mRobotDirection == Direction::right)       { mPosY -= 1; mRobotDirection = Direction::forward; }
        else if (mRobotDirection == Direction::backward)    { mPosX += 1; mRobotDirection = Direction::right; }
    } else if (dir == Direction::right) {
        if      (mRobotDirection == Direction::forward)     { mPosX += 1; mRobotDirection = Direction::right; }
        else if (mRobotDirection == Direction::left)        { mPosY -= 1; mRobotDirection = Direction::forward; }
        else if (mRobotDirection == Direction::right)       { mPosY += 1; mRobotDirection = Direction::backward; }
        else if (mRobotDirection == Direction::backward)    { mPosX -= 1; mRobotDirection = Direction::left; }
    } else if (dir == Direction::backward) {
        if      (mRobotDirection == Direction::forward)     { mPosY += 1; mRobotDirection = Direction::backward; }
        else if (mRobotDirection == Direction::left)        { mPosX += 1; mRobotDirection = Direction::right; }
        else if (mRobotDirection == Direction::right)       { mPosX -= 1; mRobotDirection = Direction::left; }
        else if (mRobotDirection == Direction::backward)    { mPosY -= 1; mRobotDirection = Direction::forward; }
    }

    if (mPosX < mMinX) mMinX = mPosX;
    if (mPosY < mMinY) mMinY = mPosY;
    if (mPosX > mMaxX) mMaxX = mPosX;
    if (mPosY > mMaxY) mMaxY = mPosY;

    // Mark visited
    mMazeArr[mPosY][mPosX].setVisited();

    printMap();
}

Direction MapData::getNextDirection() {
    return mNextDirection;
}

void MapData::setWallRecognized(bool forward, bool left, bool right) {
    if (mRobotDirection == Direction::forward) {
        mMazeArr[mPosY][mPosX].setForwardWall(forward);
        mMazeArr[mPosY - 1][mPosX].setBackwardWall(forward);

        mMazeArr[mPosY][mPosX].setLeftWall(left);
        mMazeArr[mPosY][mPosX - 1].setRightWall(left);

        mMazeArr[mPosY][mPosX].setRightWall(right);
        mMazeArr[mPosY][mPosX + 1].setLeftWall(right);

    } else if (mRobotDirection == Direction::backward) {
        mMazeArr[mPosY][mPosX].setBackwardWall(forward);
        mMazeArr[mPosY + 1][mPosX].setForwardWall(forward);

        mMazeArr[mPosY][mPosX].setRightWall(left);
        mMazeArr[mPosY][mPosX + 1].setLeftWall(left);

        mMazeArr[mPosY][mPosX].setLeftWall(right);
        mMazeArr[mPosY][mPosX - 1].setRightWall(right);

    } else if (mRobotDirection == Direction::left) {
        mMazeArr[mPosY][mPosX].setLeftWall(forward);
        mMazeArr[mPosY][mPosX - 1].setRightWall(forward);

        mMazeArr[mPosY][mPosX].setBackwardWall(left);
        mMazeArr[mPosY + 1][mPosX].setForwardWall(left);

        mMazeArr[mPosY][mPosX].setForwardWall(right);
        mMazeArr[mPosY - 1][mPosX].setBackwardWall(right);

    } else if (mRobotDirection == Direction::right) {
        mMazeArr[mPosY][mPosX].setRightWall(forward);
        mMazeArr[mPosY][mPosX + 1].setLeftWall(forward);

        mMazeArr[mPosY][mPosX].setForwardWall(left);
        mMazeArr[mPosY - 1][mPosX].setBackwardWall(left);

        mMazeArr[mPosY][mPosX].setBackwardWall(right);
        mMazeArr[mPosY + 1][mPosX].setForwardWall(right);
    }
}

void MapData::setSignRecognized(SignType signType, Direction dir) {
    mMazeArr[mPosY][mPosX].setSign(signType, dir);
}

void MapData::setSquareRecognized() {
    mMazeArr[mPosY][mPosX].setEndSquare();
}

void MapData::setRedDotRecognized() {
    mMazeArr[mPosY][mPosX].setRedDot();
}

bool MapData::isFirstGrid() {
    return mPosY == INIT_POSITION && mPosX == INIT_POSITION;
}

bool MapData::isForwardAvailable() {
    bool isWall = false;

    if (mRobotDirection == Direction::forward)
        isWall = mMazeArr[mPosY][mPosX].isForwardWall();
    else if (mRobotDirection == Direction::backward)
        isWall = mMazeArr[mPosY][mPosX].isBackwardWall();
    else if (mRobotDirection == Direction::left)
        isWall = mMazeArr[mPosY][mPosX].isLeftWall();
    else if (mRobotDirection == Direction::right)
        isWall = mMazeArr[mPosY][mPosX].isRightWall();

    return !isWall;
}

bool MapData::isLeftAvailable() {
    bool isWall = false;

    if (mRobotDirection == Direction::forward)
        isWall = mMazeArr[mPosY][mPosX].isLeftWall();
    else if (mRobotDirection == Direction::backward)
        isWall = mMazeArr[mPosY][mPosX].isRightWall();
    else if (mRobotDirection == Direction::left)
        isWall = mMazeArr[mPosY][mPosX].isBackwardWall();
    else if (mRobotDirection == Direction::right)
        isWall = mMazeArr[mPosY][mPosX].isForwardWall();

    return !isWall;
}

bool MapData::isRightAvailable() {
    bool isWall = false;

    if (mRobotDirection == Direction::forward)
        isWall = mMazeArr[mPosY][mPosX].isRightWall();
    else if (mRobotDirection == Direction::backward)
        isWall = mMazeArr[mPosY][mPosX].isLeftWall();
    else if (mRobotDirection == Direction::left)
        isWall = mMazeArr[mPosY][mPosX].isForwardWall();
    else if (mRobotDirection == Direction::right)
        isWall = mMazeArr[mPosY][mPosX].isBackwardWall();

    return !isWall;
}

void MapData::setBackTrackingMode(bool isBackTracking) {
    mIsBackTracking = isBackTracking;
}

bool MapData::isBackTrackingMode() {
    return mIsBackTracking;
}

void MapData::printMap() {
    for(int inx = mMinY; inx <= mMaxY; inx++) {
        for(int jnx = mMinX; jnx <= mMaxX; jnx++) {
            if (jnx == mMinX) {
                cout << " ";
            } else {
                cout << (mMazeArr[inx][jnx].isForwardWall() ? '-' : ' ') << " ";
            }
            
        }

        cout << endl;

        for(int jnx = mMinX; jnx <= mMaxX; jnx++) {
            if (jnx == mMinX) {
                cout << (mMazeArr[inx][jnx].isLeftWall() ? '|' : ' ');
            }            

            // Red dot, Start square, ...
            if (mPosX == jnx && mPosY == inx)
                cout << 'C';
            else if (mMazeArr[inx][jnx].isStartSquare())
                cout << 'S';
            else
                cout << ' ';

            cout << (mMazeArr[inx][jnx].isRightWall() ? '|' : ' ');
        }

        cout << endl;

        for(int jnx = mMinX; jnx <= mMaxX; jnx++) {
            if (jnx == mMinX) {
                cout << " ";
            }
            cout << (mMazeArr[inx][jnx].isBackwardWall() ? '-' : ' ') << " ";
        }

        cout << endl;
    }

    cout << "------------------------" << endl;
}

string MapData::getMazeString() {
    string str = "";
    int row, col;

    for(int inx = mMinY; inx <= mMaxY; inx++) {
        for(int jnx = mMinX; jnx <= mMaxX; jnx++) {
            row = inx - mMinY;
            col = jnx - mMinX;

            str += "{";
            str += row + ',' + col + ','; // row, column
            str += (mMazeArr[row][col].isVisited() ? 'Y' : 'N') + ',';  // visited

            // current robot direction
            if      (mRobotDirection == Direction::forward)
                str += "N,";
            else if (mRobotDirection == Direction::left)
                str += "W,";
            else if (mRobotDirection == Direction::right)
                str += "E,";
            else if (mRobotDirection == Direction::backward)
                str += "S,";

            str += (mMazeArr[row][col].isStartSquare() ? 'Y' : 'N') + ',';  // Start square
            str += (mMazeArr[row][col].isEndSquare() ? 'Y' : 'N') + ',';    // End square
            str += (mMazeArr[row][col].isRedDot() ? 'Y' : 'N') + ',';       // Red dot
            str += (mMazeArr[row][col].isForwardWall() ? 'Y' : 'N') + ',';  // Front wall
            str += (mMazeArr[row][col].isRightWall() ? 'Y' : 'N') + ',';    // Right wall
            str += (mMazeArr[row][col].isBackwardWall() ? 'Y' : 'N') + ','; // Backward wall
            str += (mMazeArr[row][col].isLeftWall() ? 'Y' : 'N') + ',';     // Left wall

            SignType st = mMazeArr[row][col].getSignType();

            if (st != SignType::SignNone) {
                if (st == SignType::SignBall) {
                    str += "B,,,,"; // TODO Direction
                }
                if (st == SignType::SignGo) {
                    str += "G,,,,"; // TODO Direction
                }
                if (st == SignType::SignStraight) {
                    str += "A,,,,"; // TODO Direction
                }
                if (st == SignType::SignStop) {
                    str += "S,,,,"; // TODO Direction
                }
            } else {
                // No sign
                str += ",,,,";
            }

            str += "}&";
        }
    }

    return str;
}
