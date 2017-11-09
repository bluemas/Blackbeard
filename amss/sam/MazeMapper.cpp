/*
 * MazeMapper.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MazeMapper.h"

MazeMapper::MazeMapper(MapRepo *mapRepo) {
    mMapRepo = mapRepo;
}

MazeMapper::~MazeMapper() {

}

void MazeMapper::init() {
    mMapRepo->init();
}

void MazeMapper::updateWallSensingEvent(WallSensingEvent *e) {

}

void MazeMapper::setNextDirection(Direction dir) {

}

void MazeMapper::printMap() {

}
