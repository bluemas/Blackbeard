/*
 * MazeMapper.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "MazeMapper.h"


MazeMapper::MazeMapper(MapData *mapData) {
    mStatus = 1;
    mMapData = mapData;
}

MazeMapper::~MazeMapper() {

}

void MazeMapper::handleWallSensingEvent(WallSensingEvent ev) {
    if ((mStatus & WALL_SENSING_ENABLE) == 1) {

        MazeGrid grid;

        if (mMapData->isFirstGrid()) {
            // Save current wall status
            mMapData->setCurrMazeGrid(grid);
        }

        if (mPrevLeftWall != ev.isLeftWall()) {
            cout << "Left wall status is changed." << endl;

            if (ev.isLeftWall()) {
                // Left wall on next grid
                cout << "Left wall" << endl;
                mMapData->setFrontMazeGrid(grid);
            } else {
                // Left open on next grid
                cout << "Left open" << endl;
            }

            mMapData->setFrontMazeGrid(grid);
            mPrevLeftWall = ev.isLeftWall();
        }
    }
}

void MazeMapper::handleRedDotRecognizedEvent(RedDotRecognizedEvent ev) {
    MazeGrid grid;
    grid.setRedDotFound();
    mMapData->setFrontMazeGrid(grid);

    cout << "Red dot recognized." << endl;
}

void MazeMapper::handleSignRecognizedEvent(SignRecognizedEvent ev) {
    MazeGrid grid;
    grid.setSignFound(ev.getSignType());
    mMapData->setCurrMazeGrid(grid);

    cout << "Sign recognized." << endl;
}

void MazeMapper::handleSquareRecognizedEvent(SquareRecognizedEvent ev) {
    MazeGrid grid;
    grid.setEndSquare();
    mMapData->setFrontMazeGrid(grid);

    cout << "Square recognized." << endl;
}
