/*
 * PathPlanner.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/PathPlanner.h"
#include "MazeMapper.h"

PathPlanner::PathPlanner(MazeMapper *mazeMapper, MapRepo *mapRepo) {
    this->mMapRepo = mapRepo;
    this->mMazeMapper = mazeMapper;
}

PathPlanner::~PathPlanner() {

}

void PathPlanner::init() {

}
