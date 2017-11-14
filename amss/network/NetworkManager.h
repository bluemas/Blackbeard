//
// Created by bluemas on 2017-10-29.
//

#ifndef BLACKBEARD_CNETWORKMANAGER_H
#define BLACKBEARD_CNETWORKMANAGER_H

#include <thread>
#include <string>
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "NetMessageEventAdapter.h"
#include "../sam/MapData.h"

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager() {}

    void start();
    void addListener(NetMessageEventAdapter* listener);
    void send(NetworkMsg type, int length, void* data);
    void sendCameraImage();
    void sendMazeData();

private:
    void initUDPPort(char* address);
    void startTCPServer();

    bool mConnected;
    bool mIPReceived;
    UDPSocket mCameraImageSendSocket;
    TCPSocket mCommandRcvSocket;
    NetMessageEventAdapter* mListener;
    TTcpListenPort* mListenPort;
    TTcpConnectedPort* mClientPort;
    TUdpDest* mRUIUDPDest;
    TUdpLocalPort* mRUIUDPPort;
    std::thread* mSvrThread;
    std::thread* mImageSender;
    std::thread* mMazeSender;

    void establishTcpConnection();
};
#endif //BLACKBEARD_CNETWORKMANAGER_H
