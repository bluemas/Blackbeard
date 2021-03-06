/*
 * WallSensingEvent.h
 *
 *  Created on: 2017. 11. 8.
 *      Author: gtlove
 */

#ifndef SAM_WALLSENSINGEVENT_H_
#define SAM_WALLSENSINGEVENT_H_

#include "EventBase.h"
#include "../../common/Constants.h"

class WallSensingEvent: public EventBase {
public:
    WallSensingEvent();
    virtual ~WallSensingEvent();

    unsigned char getWallStatus();
    bool isFrontWall();
    bool isLeftWall();
    bool isRightWall();
    void setFrontWall();
    void setLeftWall();
    void setRightWall();
private:
    unsigned char mWallStatus;
};

#endif /* SAM_WALLSENSINGEVENT_H_ */
