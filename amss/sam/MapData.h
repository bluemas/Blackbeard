/*
 * MapRepo.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAPDATA_H_
#define SAM_MAPDATA_H_

#include <iostream>
#include <string>
#include "../common/Constants.h"
#include "MazeGrid.h"

using namespace std;

class MapData {

public:
    virtual ~MapData();

    static MapData* getInstance();

    void init();
    void setNextDirection(Direction dir);
    Direction getNextDirection();
    void setWallRecognized(bool forward, bool left, bool right);
    void setSignRecognized(SignType signType, Direction dir);
    void setSquareRecognized();
    void setRedDotRecognized();
    void getMapData();
    bool isFirstGrid();
    bool isForwardAvailable();
    bool isLeftAvailable();
    bool isRightAvailable();
    void setBackTrackingMode(bool isBackTracking);
    bool isBackTrackingMode();
    void printMap();
    string getMazeString();

private:
    static const int MAZE_SIZE = 20;
    static const int INIT_POSITION = MAZE_SIZE / 2;

    MapData();

    static MapData *sInstance;
    bool mFirstGrid = true;
    int mPosX = INIT_POSITION, mPosY = INIT_POSITION, mMinX = INIT_POSITION,
        mMinY = INIT_POSITION, mMaxX = INIT_POSITION, mMaxY = INIT_POSITION;
    MazeGrid mMazeArr[MAZE_SIZE][MAZE_SIZE];
    Direction mRobotDirection = Direction::forward;
    Direction mNextDirection = Direction::forward;
    bool mIsBackTracking = false;
};

#endif /* SAM_MAPDATA_H_ */
