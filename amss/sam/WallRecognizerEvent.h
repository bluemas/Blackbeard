/*
 * WallRecognizerEvent.h
 *
 *  Created on: 2017. 11. 5.
 *      Author: gtlove
 */

#ifndef SAM_WALLRECOGNIZEREVENT_H_
#define SAM_WALLRECOGNIZEREVENT_H_

#include "../common/EventBase.h"

class WallRecognizerEvent: public EventBase {
public:
    WallRecognizerEvent();
    virtual ~WallRecognizerEvent();
};

#endif /* SAM_WALLRECOGNIZEREVENT_H_ */
