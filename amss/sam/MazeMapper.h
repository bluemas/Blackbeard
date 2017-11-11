/*
 * MazeMapper.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEMAPPER_H_
#define SAM_MAZEMAPPER_H_

#include <iostream>
#include "../common/Constants.h"
#include "../common/event/WallSensingEventHandler.h"
#include "MapData.h"

using namespace std;

class MazeMapper : public WallSensingEventHandler {

public:
    MazeMapper(MapData *mapData);
    virtual ~MazeMapper();

    void handleWallSensingEvent(WallSensingEvent ev);

private:
    MapData *mMapData;
};


#endif /* SAM_MAZEMAPPER_H_ */
