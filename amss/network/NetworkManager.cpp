//
// Created by bluemas on 2017-10-29.
//

#include "NetworkManager.h"
#include <thread>

// TODO : �ʱ�ȭ �Ķ���� ���� �ʿ�(��¿�, ������)
// - ���� �ӵ�, ...

NetworkManager::NetworkManager() {

}

void NetworkManager::addListener(NetMessageEventAdapter* listener) {
    mListener = listener;
}

void NetworkManager::start() {
    initDevices();
    std::thread t(&NetworkManager::startTCPServer, this);
    t.join();
}

void NetworkManager::initDevices() {
    //TODO : Not implemented
}

void NetworkManager::startTCPServer() {
    //TODO : Not implemented
}

void NetworkManager::send() {
    //TODO : Not implemented
}
