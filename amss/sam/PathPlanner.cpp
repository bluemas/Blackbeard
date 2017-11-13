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

    mCount = 0; // TODO remove
}

Direction PathPlanner::nextDirection() {
    Direction dir = Direction::none;

    // TODO Find next direction using MapRepo

    if (mCount == 0) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 1) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 2) {
        cout << "Move right in PathPlanning" << endl;
        dir = Direction::right;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 3) {
        cout << "Move front in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 4) {
        cout << "Move right in PathPlanning" << endl;
        dir = Direction::right;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 5) {
        cout << "Move none in PathPlanning" << endl;
        dir = Direction::none;
        mMapData->setNextDirection(dir);
        mCount++;
    }

    return dir;
}
