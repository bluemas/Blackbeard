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

void MazeMapper::handleWallSensingEvent(const WallSensingEvent ev) {
    cout << "Received WallSensingEvnet" << endl;
}

void MazeMapper::handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev) {
    cout << "Received RedDotRecognizedEvent" << endl;
}

void MazeMapper::handleSignRecognizedEvent(const SignRecognizedEvent ev){
    cout << "Received SignRecognizedEvent" << endl;
}

void MazeMapper::handleSquareRecognizedEvent(const SquareRecognizedEvent ev) {
    cout << "Received SquareRecognizedEvent" << endl;
}
