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
#include "MapData.h"

class MazeMapper : public WallSensingEventHandler {

public:
    MazeMapper(MapData *mapData);
    virtual ~MazeMapper();

    void handleWallSensingEvent(const WallSensingEvent ev);

private:
    MapData *mMapData;
};


#endif /* SAM_MAZEMAPPER_H_ */
