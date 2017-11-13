/*
 * PathPlanner.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_PATHPLANNER_H_
#define SAM_PATHPLANNER_H_

#include <iostream>
#include "../common/Constants.h"
#include "MapData.h"
#include "MazeMapper.h"

using namespace std;

class PathPlanner {
public:
    PathPlanner();
    PathPlanner(MapData *mapData);
    virtual ~PathPlanner();

    void init();
    Direction nextDirection();

private:
    MapData *mMapData;

    int mCount = 0; // TEMP
};

#endif /* SAM_PATHPLANNER_H_ */
