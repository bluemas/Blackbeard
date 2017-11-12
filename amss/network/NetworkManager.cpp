//
// Created by bluemas on 2017-10-29.
//

#include "NetworkManager.h"
#include "../common/Logging.h"
#include "../common/Constants.h"
#include <thread>
#include <iostream>
#include <cstring>

#define TCP_RECV_PORT 3001
#define SEND_BUFFER_SIZE 1024
#define RECV_BUFFER_SIZE 1024
#define RUI_ADDRESS "192.168.253.1"
#define RUI_PORT "3000"

NetworkManager::NetworkManager() :
    mConnected(false) {
}

void NetworkManager::addListener(NetMessageEventAdapter* listener) {
    mListener = listener;
}

void NetworkManager::start() {
    init();

    // Start TCP Server
    mSvrThread = new std::thread(&NetworkManager::startTCPServer, this);

    // Start Camera Image Sender
    mImageSender = new std::thread(&NetworkManager::sendCameraImage, this);
}

void NetworkManager::init() {
    //TODO : Not implemented
    mRUIUDPDest = mCameraImageSendSocket.GetUdpDest(RUI_ADDRESS, RUI_PORT);
    mRUIUDPPort = mCameraImageSendSocket.OpenUdpPort(3000);
}

void NetworkManager::startTCPServer() {
    establishTcpConnection();

    // Read TCP Data
    unsigned char msg[RECV_BUFFER_SIZE] = { 0 };
    bool runLoop = true;
    while (runLoop) {
        ssize_t recvLen = mCommandRcvSocket.ReadDataTcp(
            mClientPort, msg, RECV_BUFFER_SIZE);
        if (recvLen > 0) {
            int payloadLen = 0;
            memcpy(&payloadLen, &msg[1], sizeof(int));
            //FIXME : Remove following comments
//            if (payloadLen != (recvLen - 5)) {
//                Logging::logOutput(Logging::ERROR,
//                                   "Received command message corrupted.");
//                continue;
//            }

            // FIXME : Remove test code
//            char temp[2] { 0 };
//            snprintf(temp, 2, "%c", msg[0]);
//            mListener->handleMessage(atoi(temp), &msg[5]);
            mListener->handleMessage(NetworkMsg(msg[0]), &msg[5]);
        }
        else {
            // Notify network connection
            mConnected = false;
            mListener->handleMessage(NetworkMsg::NetworkDisconnection, NULL);

            // Try to reestablish connection
            establishTcpConnection();
            Logging::logOutput(Logging::ERROR, "Trying to reestablish network.");
        }
    }
}

void NetworkManager::establishTcpConnection() {// Listen TCP Port
    if (mListenPort != NULL)
        mCommandRcvSocket.CloseTcpListenPort(&mListenPort);

    mListenPort = mCommandRcvSocket.OpenTcpListenPort(TCP_RECV_PORT);

    if (mListenPort == NULL)
        Logging::logOutput(Logging::ERROR, "TCP Socket Listen Failed.");

    // Accept TCP Port
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    if (mClientPort != NULL)
        mCommandRcvSocket.CloseTcpConnectedPort(&mClientPort);

    mClientPort = mCommandRcvSocket.AcceptTcpConnection(
            mListenPort, &client_addr, &len);

    if (mClientPort == NULL)
        Logging::logOutput(Logging::ERROR, "TCP Socket Accept Failed.");
    else
        mConnected = true;

    // Notify network connection
    mListener->handleMessage(NetworkMsg::NetworkConnection, NULL);

    Logging::logOutput(Logging::INFO, "TCP Connection is established.");
}

void NetworkManager::send(NetworkMsg type, int length, void* data) {
    char msg[SEND_BUFFER_SIZE] = { 0 };
    int msgLen = sizeof(char) + sizeof(int) + length;
    switch (type) {
        case NetworkMsg::SensorData:
        case NetworkMsg::RobotMode:
        case NetworkMsg::RobotStatusMessage:
        case NetworkMsg::MazeSovlingCompleted:
        case NetworkMsg::RobotInitialized:
            msg[0] = (char)type;
            memcpy(&msg[1], &length, sizeof(int));
            memcpy(&msg[5], data, length);
            break;
        case NetworkMsg::MazeMap:
            // TODO : How does Maze Map be sent?
//            sprintf(msg, "%c%d%s", type, length, (char*)data);
            break;
    }

//    std::cout << "[(" << (int)type << ") " << msgLen << ": " << (char*)&msg[5] << "]" << std::endl;
    mCommandRcvSocket.WriteDataTcp(mClientPort,
                                   reinterpret_cast<unsigned char *>(msg), msgLen);
}

void NetworkManager::sendCameraImage() {
    while (true) {
        if (mConnected) {
            // TODO : Retrieve camera image from image repo

            // TODO : Send JPEG Image to RUI
            //        cv::imencode(".jpg", Image, sendbuff, param);
            //        return(SendUDPMsg(UdpLocalPort,dest,sendbuff.data(), sendbuff.size()));

            //        mCameraImageSendSocket.SendUDPMsg(mRUIUDPPort, mRUIUDPDest, ,);

            // REVIEW : Determine the period of camara image transmission
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
