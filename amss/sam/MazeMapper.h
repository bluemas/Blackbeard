/*
 * MazeMapper.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEMAPPER_H_
#define SAM_MAZEMAPPER_H_

#include "../common/SensingEventBase.h"
#include "../common/Constants.h"

#include "MapRepo.h"

class MazeMapper {

public:
    MazeMapper(MapRepo *mapRepo);
    virtual ~MazeMapper();

    void init();
    void notify(SensingEventBase e);
    void setNextDirection(Direction dir);

private:
    MapRepo *m_MapRepo;
};


#endif /* SAM_MAZEMAPPER_H_ */
