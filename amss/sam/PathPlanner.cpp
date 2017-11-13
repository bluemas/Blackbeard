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

    /*
    // Return previous direction if the mode is back tracking
    if (mMapData->isBackTrackingMode() && !mDirStack.empty()) {
        dir = mDirStack.top();
        mDirStack.pop();
        return dir;
    }

    // Find next direction by the left hand rule
    if (mMapData->isLeftAvailable()) {
        dir = Direction::left;
    } else if (mMapData->isForwardAvailable()) {
        dir = Direction::forward;
    } else if (mMapData->isRightAvailable()) {
        dir = Direction::right;
    } else if (isMappedComplete()){
        return Direction::none;
    } else {
        // No way to go.
        return Direction::backward;
    }

    // Push a direction to the stack for back tracking
    if (!mMapData->isBackTrackingMode()) {
        mDirStack.push(dir);
    }
    */

    // TEST CODE!!!
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
        cout << "Move right in PathPlanning" << endl;
        dir = Direction::right;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 6) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 7) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 8) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 9) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 10) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 11) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 12) {
        cout << "Move none in PathPlanning" << endl;
        dir = Direction::none;
        mMapData->setNextDirection(dir);
        mCount++;
    }

    return dir;
}

bool PathPlanner::isMappedComplete() {
    // TODO Check whether a maze is mapped completely
    return false;
}
