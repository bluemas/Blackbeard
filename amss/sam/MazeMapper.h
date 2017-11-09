/*
 * MazeMapper.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEMAPPER_H_
#define SAM_MAZEMAPPER_H_

#include "../common/Constants.h"
#include "../common/event/WallSensingEventHandler.h"
#include "MapRepo.h"

class MazeMapper : public WallSensingEventHandler {

public:
    MazeMapper(MapRepo *mapRepo);
    virtual ~MazeMapper();

    void init();
    void handleWallSensingEvent(const WallSensingEvent ev);

private:
    MapRepo *mMapRepo;
};


#endif /* SAM_MAZEMAPPER_H_ */
