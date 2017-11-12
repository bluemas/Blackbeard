/*
 * MazeGrid.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/MazeGrid.h"

MazeGrid::MazeGrid() {

}

MazeGrid::~MazeGrid() {

}

void MazeGrid::setRedDotFound() {
    mRedDotFound = true;
}

void MazeGrid::setSignFound(SignType signType) {
    mSignType = signType;
}

void MazeGrid::setEndSquare() {
    mEndSqureFound = true;
}
