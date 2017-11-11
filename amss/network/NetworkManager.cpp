//
// Created by bluemas on 2017-10-29.
//

#include "NetworkManager.h"
#include <thread>

// TODO : 초기화 파라미터 정의 필요(양승완, 윤태희)

NetworkManager::NetworkManager() {

}

NetworkManager::~NetworkManager() {

}

void NetworkManager::addListener(NetMessageEventAdapter* listener) {
    mListener = listener;
}

void NetworkManager::start() {
    NetworkManager* networkManager = new NetworkManager();
    networkManager->init();
    std::thread t(&NetworkManager::startTCPServer, networkManager);
    t.join();
}

void NetworkManager::init() {
    //TODO : Not implemented
}

void NetworkManager::startTCPServer() {
    //TODO : Not implemented
}

void NetworkManager::send() {
    //TODO : Not implemented
}
