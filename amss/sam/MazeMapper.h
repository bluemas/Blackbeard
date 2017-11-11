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
#include "../common/event/RedDotRecognizedEventHandler.h"
#include "../common/event/SignRecognizedEventHandler.h"
#include "../common/event/SquareRecognizedEventHandler.h"

#include "MapRepo.h"

using namespace std;

class MazeMapper : public WallSensingEventHandler,
                   public RedDotRecognizedEventHandler,
                   public SignRecognizedEventHandler,
                   public SquareRecognizedEventHandler {

public:
    MazeMapper(MapRepo *mapRepo);
    virtual ~MazeMapper();

    void handleWallSensingEvent(const WallSensingEvent ev);
    void handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev);
    void handleSignRecognizedEvent(const SignRecognizedEvent ev);
    void handleSquareRecognizedEvent(const SquareRecognizedEvent ev);

private:
    MapRepo *mMapRepo;
};


#endif /* SAM_MAZEMAPPER_H_ */
