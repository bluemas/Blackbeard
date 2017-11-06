//
// Created by bluem on 2017-11-05.
//

#ifndef AMSS_IMESSAGEHANDLER_H
#define AMSS_IMESSAGEHANDLER_H


class IMessageListener {
    virtual void handleMessage(int type, void* payload) = 0;
};


#endif //AMSS_IMESSAGEHANDLER_H
