/*
 * MapRepo.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAPDATA_H_
#define SAM_MAPDATA_H_

#include "../common/Constants.h"
#include "MazeGrid.h"

class MapData {

public:
    MapData();
    virtual ~MapData();

    void init();
    void setNextDirection(Direction dir);
    Direction getNextDirection();
    MazeGrid getCurrMazeGrid();
    void setCurrMazeGrid(MazeGrid grid);
    void setFrontMazeGrid(MazeGrid grid);
    void getMapData();
    void printMap();
    bool isFirstGrid();

private:
    static const int MAZE_SIZE = 10;
    bool mFirstGrid = true;
    int mPosX = 5, mPosY = 10;
    Direction mRobotDirection = Direction::forward;
    MazeGrid mMazeArr[MAZE_SIZE][MAZE_SIZE];
    Direction mNextDirection = Direction::forward;

    void mergeGrid(MazeGrid g1, MazeGrid g2);
};

#endif /* SAM_MAPDATA_H_ */
