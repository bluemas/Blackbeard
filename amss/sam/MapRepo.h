/*
 * MapRepo.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAPREPO_H_
#define SAM_MAPREPO_H_

#include "../common/Constants.h"
#include "MazeGrid.h"

class MapRepo {

public:
    MapRepo();
    virtual ~MapRepo();

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

#endif /* SAM_MAPREPO_H_ */
