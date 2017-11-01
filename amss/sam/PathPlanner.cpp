/*
 * PathPlanner.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/PathPlanner.h"
#include "MazeMapper.h"

PathPlanner::PathPlanner() {
    // Initiate MapRepo
    m_MapRepo = new MapRepo();

    // Initiate MazeMapper
    m_MazeMapper = new MazeMapper(m_MapRepo);

}

PathPlanner::~PathPlanner() {

}

void PathPlanner::init() {

}
