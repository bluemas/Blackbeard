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
    MapRepo *m_MapRepo;
    MazeMapper *m_MazeMapper;

    PathPlanner();
    virtual ~PathPlanner();

    void init();
    Direction nextDirection();

private:

};

#endif /* SAM_PATHPLANNER_H_ */
