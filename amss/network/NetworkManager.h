//
// Created by bluem on 2017-10-29.
//

#ifndef BLACKBEARD_CNETWORKMANAGER_H
#define BLACKBEARD_CNETWORKMANAGER_H

#include "UDPSocket.h"
#include "TCPSocket.h"
#include "IMessageListener.h"

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    static void start();

    void addListener(IMessageListener* listener);

private:
    void init();
    void startTCPServer();

    UDPSocket mCameraImageSendSocket;
    TCPSocket mCommandRecvSocket;
    IMessageListener* mListener;
};
#endif //BLACKBEARD_CNETWORKMANAGER_H
