/*
 * PathPlanner.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_PATHPLANNER_H_
#define SAM_PATHPLANNER_H_

#include "../common/Constants.h"
#include "MapData.h"
#include "MazeMapper.h"

class PathPlanner {
public:
    PathPlanner();
    PathPlanner(MapData *mapRepo);
    virtual ~PathPlanner();

    void initDevices();
    Direction nextDirection();

private:
    MapData *mMapData;
};

#endif /* SAM_PATHPLANNER_H_ */
