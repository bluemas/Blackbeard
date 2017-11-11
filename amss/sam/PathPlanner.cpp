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
}

PathPlanner::~PathPlanner() {

}

void PathPlanner::initDevices() {

}

Direction PathPlanner::nextDirection() {
    Direction dir = Direction::forward;

    // TODO Find next direction using MapRepo

    mMapData->setNextDirection(dir);

    return dir;
}
