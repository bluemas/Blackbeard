/*
 * PathPlanner.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/PathPlanner.h"

PathPlanner::PathPlanner(MapRepo *mapRepo) {
    mMapRepo = mapRepo;
    init();
}

PathPlanner::~PathPlanner() {

}

void PathPlanner::init() {
    mMapRepo->init();
}

Direction PathPlanner::nextDirection() {
    Direction dir = Direction::right;

    // TODO Find next direction using MapRepo

    mMapRepo->setNextDirection(dir);

    return dir;
}
