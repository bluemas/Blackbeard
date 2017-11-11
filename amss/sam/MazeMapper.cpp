/*
 * MazeMapper.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MazeMapper.h"

MazeMapper::MazeMapper(MapRepo *mapRepo) {
    mMapRepo = mapRepo;
    init();
}

MazeMapper::~MazeMapper() {

}

void MazeMapper::init() {
    mMapRepo->init();
}

void MazeMapper::handleWallSensingEvent(const WallSensingEvent ev) {

}
