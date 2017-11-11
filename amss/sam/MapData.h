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

    void getMapData();
    void printMap();

private:
    static const int MAZE_SIZE = 10;

    MazeGrid mazeArr[MAZE_SIZE][MAZE_SIZE];
    Direction mNextDirection = Direction::forward;
};

#endif /* SAM_MAPDATA_H_ */
