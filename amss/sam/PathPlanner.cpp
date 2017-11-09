/*
 * PathPlanner.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/PathPlanner.h"
#include "MazeMapper.h"

PathPlanner::PathPlanner() {

}

PathPlanner::PathPlanner(MazeMapper *mazeMapper, MapRepo *mapRepo) {
    mMapRepo = mapRepo;
    mMazeMapper = mazeMapper;
}

PathPlanner::~PathPlanner() {

}

void PathPlanner::init() {

}

Direction PathPlanner::nextDirection() {
    // TODO Find next direction using MapRepo
    return Direction::forward;
}
