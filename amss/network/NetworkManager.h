//
// Created by bluemas on 2017-10-29.
//

#ifndef BLACKBEARD_CNETWORKMANAGER_H
#define BLACKBEARD_CNETWORKMANAGER_H

#include <thread>
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "NetMessageEventAdapter.h"

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager() {}

    void start();
    void addListener(NetMessageEventAdapter* listener);
    void send(NetworkMsg type, int length, void* data);
    void sendCameraImage();

private:
    void init();
    void startTCPServer();

    bool mConnected;
    UDPSocket mCameraImageSendSocket;
    TCPSocket mCommandRcvSocket;
    NetMessageEventAdapter* mListener;
    TTcpListenPort* mListenPort;
    TTcpConnectedPort* mClientPort;
    TUdpDest* mRUIUDPDest;
    TUdpLocalPort* mRUIUDPPort;
    std::thread* mSvrThread;
    std::thread* mImageSender;

    void establishTcpConnection();
};
#endif //BLACKBEARD_CNETWORKMANAGER_H
