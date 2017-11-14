/*
 * MazeMapper.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEMAPPER_H_
#define SAM_MAZEMAPPER_H_

#include <iostream>
#include <atomic>
#include "../common/Constants.h"
#include "../common/event/WallSensingEventHandler.h"
#include "../common/event/CrossRecognizedEventHandler.h"
#include "../common/event/RedDotRecognizedEventHandler.h"
#include "../common/event/SignRecognizedEventHandler.h"
#include "../common/event/SquareRecognizedEventHandler.h"
#include "MapData.h"

using namespace std;

class MazeMapper :
        public WallSensingEventHandler,
        public CrossRecognizedEventHandler,
        public RedDotRecognizedEventHandler,
        public SignRecognizedEventHandler,
        public SquareRecognizedEventHandler {

public:
    MazeMapper();
    virtual ~MazeMapper();

    void handleWallSensingEvent(WallSensingEvent ev);
    void handleCrossRecognizedEvent(CrossRecognizedEvent ev);
    void handleRedDotRecognizedEvent(RedDotRecognizedEvent ev);
    void handleSignRecognizedEvent(SignRecognizedEvent ev);
    void handleSquareRecognizedEvent(SquareRecognizedEvent ev);

private:
    MapData *mMapData;
    bool mPrevLeftWall = false;
    bool mPrevRightWall = false;
};

#endif /* SAM_MAZEMAPPER_H_ */
