//
// Created by bluem on 2017-10-29.
//

#include "NetworkManager.h"
#include <thread>

NetworkManager::NetworkManager() {

}

NetworkManager::~NetworkManager() {

}

void NetworkManager::addListener(IMessageListener* listener) {
    mListener = listener;
}

void NetworkManager::start() {
    NetworkManager* networkManager = new NetworkManager();
    networkManager->init();
    std::thread t(&NetworkManager::startTCPServer, networkManager);
    t.join();
}

void NetworkManager::init() {
    //TODO
}

void NetworkManager::startTCPServer() {
    //TODO
}
