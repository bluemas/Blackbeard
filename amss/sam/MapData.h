/*
 * MapRepo.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAPDATA_H_
#define SAM_MAPDATA_H_

#include <iostream>
#include "../common/Constants.h"

using namespace std;

class MapData {

public:
    MapData();
    virtual ~MapData();

    void init();
    void setNextDirection(Direction dir);
    Direction getNextDirection();
    //MazeGrid getCurrMazeGrid();
    //void setCurrMazeGrid(MazeGrid grid);
    //void setFrontMazeGrid(MazeGrid grid);
    void setMazeStatus(char front, char left, char right, char floor);
    void getMapData();
    void printMap();
    bool isFirstGrid();

private:
    static const int MAZE_SIZE = 20;
    bool mFirstGrid = true;
    int mPosX = 10, mPosY = 10;
    char mMazeArr[MAZE_SIZE][MAZE_SIZE];
    //MazeGrid mMazeArr[MAZE_SIZE][MAZE_SIZE];
    Direction mRobotDirection = Direction::forward;
    Direction mNextDirection = Direction::forward;
};

#endif /* SAM_MAPDATA_H_ */
