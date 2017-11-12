//
// Created by bluemas on 2017-11-05.
//

#ifndef AMSS_IMESSAGEHANDLER_H
#define AMSS_IMESSAGEHANDLER_H

#include "../common/Constants.h"

class NetMessageEventAdapter {
public:
    virtual void handleMessage(NetworkMsg type, void* data) {}
    virtual void handleDisconnectionEvent() {}
};


#endif //AMSS_IMESSAGEHANDLER_H
