/*
 * MazeMapper.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MazeMapper.h"
//#include "../common/Utils.h"

MazeMapper::MazeMapper(MapData *mapData) {
    //mStatus = 1;
    mMapData = mapData;
}

MazeMapper::~MazeMapper() {

}

void MazeMapper::handleWallSensingEvent(WallSensingEvent ev) {
    char timeStr[256] = { 0 };
    int h, m, s;

//    getTimeStr(h, m, s);
//    snprintf(timeStr, 256, "%02d:%02d:%02d", h, m, s);
    cout << /*timeStr <<*/ " :  Wall recognized. L : "<< ev.isLeftWall() << ", F " << ev.isFrontWall() << ", R : " << ev.isRightWall() << endl;
    mMapData->setWallRecognized(ev.isFrontWall(), ev.isLeftWall(), ev.isRightWall());

    //mMapData->printMap();
}

void MazeMapper::handleCrossRecognizedEvent(CrossRecognizedEvent ev) {
    cout << "- Cross recognized." << endl;

    mMapData->printMap();
}

void MazeMapper::handleRedDotRecognizedEvent(RedDotRecognizedEvent ev) {
    mMapData->setRedDotRecognized();

    cout << "- Red dot recognized." << endl;

    mMapData->printMap();
}

void MazeMapper::handleSignRecognizedEvent(SignRecognizedEvent ev) {
    mMapData->setSignRecognized(ev.getSignType(), Direction::right); // FIXME

    cout << "- Sign recognized." << endl;

    mMapData->printMap();
}

void MazeMapper::handleSquareRecognizedEvent(SquareRecognizedEvent ev) {
    mMapData->setSquareRecognized();

    cout << "- Square recognized." << endl;

    mMapData->printMap();
}
