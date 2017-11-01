/*
 * MazeMapper.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/MazeMapper.h"

MazeMapper::MazeMapper(MapRepo *mapRepo) {
    m_MapRepo = mapRepo;
}

MazeMapper::~MazeMapper() {
    delete m_MapRepo;
}

void MazeMapper::init() {
    delete m_MapRepo;
    m_MapRepo = new MapRepo();
}

void MazeMapper::notify(SensingEventBase e) {

}
void MazeMapper::setNextDirection(Direction dir) {

}
