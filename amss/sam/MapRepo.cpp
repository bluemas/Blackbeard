/*
 * MapRepo.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MapRepo.h"


MapRepo::MapRepo() {

}


MapRepo::~MapRepo() {

}

void MapRepo::initDevices() {
    // TODO initDevices MapRepo
}

void MapRepo::setNextDirection(Direction dir) {
    mNextDirection = dir;
}

Direction MapRepo::getNextDirection() {
    return mNextDirection;
}
