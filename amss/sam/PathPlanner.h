/*
 * PathPlanner.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_PATHPLANNER_H_
#define SAM_PATHPLANNER_H_

#include "../common/Constants.h"
#include "MapRepo.h"
#include "MazeMapper.h"

class PathPlanner {
public:
    MapRepo *mMapRepo;
    MazeMapper *mMazeMapper;

    PathPlanner();
    PathPlanner(MazeMapper *mazeMapper, MapRepo *mapRepo);
    virtual ~PathPlanner();

    void init();
    Direction nextDirection();
};

#endif /* SAM_PATHPLANNER_H_ */
