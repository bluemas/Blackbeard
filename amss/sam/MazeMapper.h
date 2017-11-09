/*
 * MazeMapper.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEMAPPER_H_
#define SAM_MAZEMAPPER_H_

#include "../common/Constants.h"
#include "../common/event/WallSensingEvent.h"
#include "MapRepo.h"

class MazeMapper {

public:
    MazeMapper(MapRepo *mapRepo);
    virtual ~MazeMapper();

    void init();
    void updateWallSensingEvent(WallSensingEvent *e);

private:
    MapRepo *mMapRepo;
};


#endif /* SAM_MAZEMAPPER_H_ */
