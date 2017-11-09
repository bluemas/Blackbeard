/*
 * WallSensingEvent.h
 *
 *  Created on: 2017. 11. 8.
 *      Author: gtlove
 */

#ifndef SAM_WALLSENSINGEVENT_H_
#define SAM_WALLSENSINGEVENT_H_

#include "../common/SensingEventBase.h"
#include "../common/Constants.h"

class WallSensingEvent: public SensingEventBase {
public:
    WallSensingEvent(unsigned char wallStatus);
    virtual ~WallSensingEvent();

    bool isFrontWall();
    bool isLeftWall();
    bool isRightWall();
private:
    unsigned char mWallStatus;
};

#endif /* SAM_WALLSENSINGEVENT_H_ */
