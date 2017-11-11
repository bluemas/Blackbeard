/*
 * PathPlanner.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/PathPlanner.h"

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
    Direction dir = Direction::right;

    // TODO Find next direction using MapRepo

    mMapData->setNextDirection(dir);

    return dir;
}
