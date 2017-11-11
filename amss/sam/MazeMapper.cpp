/*
 * MazeMapper.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MazeMapper.h"

MazeMapper::MazeMapper(MapData *mapData) {
    mMapData = mapData;
}

MazeMapper::~MazeMapper() {

}

void MazeMapper::handleWallSensingEvent(const WallSensingEvent ev) {

}
