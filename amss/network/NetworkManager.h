//
// Created by bluemas on 2017-10-29.
//

#ifndef BLACKBEARD_CNETWORKMANAGER_H
#define BLACKBEARD_CNETWORKMANAGER_H

#include "UDPSocket.h"
#include "TCPSocket.h"
#include "NetMessageEventAdapter.h"

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager() {}

    void start();
    void send();
    void addListener(NetMessageEventAdapter* listener);

private:
    void initDevices();
    void startTCPServer();

    UDPSocket mCameraImageSendSocket;
    TCPSocket mCommandRecvSocket;
    NetMessageEventAdapter* mListener;
};
#endif //BLACKBEARD_CNETWORKMANAGER_H
