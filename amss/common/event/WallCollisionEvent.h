/*
 * WallRecognizerEvent.h
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#ifndef COMMON_EVENT_WALLCOLLISIONEVENT_H_
#define COMMON_EVENT_WALLCOLLISIONEVENT_H_

#include "EventBase.h"

class WallCollisionEvent: public EventBase {
public:
    WallCollisionEvent();
    virtual ~WallCollisionEvent();

    bool isWarnCollision();
    int getFrontDistance();
    int getLeftDistance();
    int getRightDistance();
    void setFrontDistance(int val);
    void setLeftDistance(int val);
    void setRightDistance(int val);
private:
    int mFrontDistance = -1;
    int mLeftDistance = -1;
    int mRightDistance = -1;
};

#endif /* COMMON_EVENT_WALLCOLLISIONEVENT_H_ */
