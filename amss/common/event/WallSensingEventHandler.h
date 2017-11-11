/*
 * IWallSensingEventHandler.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_WALLSENSINGEVENTHANDLER_H_
#define COMMON_EVENT_WALLSENSINGEVENTHANDLER_H_

#include "WallSensingEvent.h"

class WallSensingEventHandler {
public:
    virtual ~WallSensingEventHandler();
    virtual void handleWallSensingEvent(WallSensingEvent ev) = 0;
};

#endif /* COMMON_EVENT_WALLSENSINGEVENTHANDLER_H_ */
