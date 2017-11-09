/*
 * IWallCollisionEventHandler.h
 *
 *  Created on: 2017. 11. 9.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_WALLCOLLISIONEVENTHANDLER_H_
#define COMMON_EVENT_WALLCOLLISIONEVENTHANDLER_H_

#include "WallCollisionEvent.h"

class WallCollisionEventHandler {
public:
    virtual ~WallCollisionEventHandler();
    virtual void handleWallCollisionEvent(const WallCollisionEvent ev) = 0;
};

#endif /* COMMON_EVENT_WALLCOLLISIONEVENTHANDLER_H_ */
