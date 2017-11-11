/*
 * MapRepo.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAPREPO_H_
#define SAM_MAPREPO_H_

#include "../common/Constants.h"


class MapRepo {

public:
    MapRepo();
    virtual ~MapRepo();

    void init();
    void setNextDirection(Direction dir);
    Direction getNextDirection();

    void getMapData();
    void printMap();

private:
    Direction mNextDirection;
};

#endif /* SAM_MAPREPO_H_ */
