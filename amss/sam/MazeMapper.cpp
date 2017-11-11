/*
 * MazeMapper.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MazeMapper.h"

MazeMapper::MazeMapper(MapRepo *mapRepo) {
    mMapRepo = mapRepo;
    initDevices();
}

MazeMapper::~MazeMapper() {

}

void MazeMapper::initDevices() {
    mMapRepo->initDevices();
}

void MazeMapper::handleWallSensingEvent(const WallSensingEvent ev) {

}
