/*
 * PathPlanner.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_PATHPLANNER_H_
#define SAM_PATHPLANNER_H_

#include "../common/Constants.h"

class PathPlanner {
public:
    PathPlanner();
    virtual ~PathPlanner();

    Direction nextDirection();

private:

};

#endif /* SAM_PATHPLANNER_H_ */
