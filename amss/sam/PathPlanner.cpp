/*
 * PathPlanner.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/PathPlanner.h"
#include "MazeMapper.h"

PathPlanner::PathPlanner(MapData *mapData) {
    mMapData = mapData;
    init();
}

PathPlanner::~PathPlanner() {

}

void PathPlanner::init() {
    mMapData->init();
}

Direction PathPlanner::nextDirection() {
    Direction dir = Direction::forward;

    // TODO Find next direction using MapRepo

    if (mCount == 0) {
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 1) {
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 2) {
        dir = Direction::right;
        mMapData->setNextDirection(dir);
        mCount++;
    }

    return dir;
}
