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

        if (ev.isFrontWall()) {
            mMapData->setMazeStatus('*', '\0', '\0', '\0');
        }

        if (ev.isLeftWall() && ev.isRightWall()) {
            mMapData->setMazeStatus('\0', '*', '*', '\0');
        }

        if (ev.isLeftWall() && !ev.isRightWall()) {
            mMapData->setMazeStatus('\0', '*', ' ', '\0');
        }

        if (!ev.isLeftWall() && ev.isRightWall()) {
            mMapData->setMazeStatus('\0', ' ', '*', '\0');
        }

        mMapData->printMap();

        /*
        MazeGrid grid;

        if (mMapData->isFirstGrid()) {
            // Save current wall status
            //mMapData->setCurrMazeGrid(grid);
        }

        if (mPrevLeftWall != ev.isLeftWall()) {
            if (ev.isLeftWall()) {
                // Left wall on next grid
                cout << "Left wall" << endl;
                //mMapData->setFrontMazeGrid(grid);
            } else {
                // Left open on next grid
                cout << "Left open" << endl;
            }

//            mMapData->setFrontMazeGrid(grid);
//            mPrevLeftWall = ev.isLeftWall();
        }

        if (mPrevRightWall != ev.isRightWall()) {
            if (ev.isRightWall()) {
                cout << "Right wall" << endl;
            } else {
                cout << "Right open" << endl;
            }
        }
        */
    }
}

void MazeMapper::handleCrossRecognizedEvent(CrossRecognizedEvent ev) {
    //mMapData->setMazeStatus('\0', '\0', '\0', ' ');

    cout << "- Cross recognized." << endl;

    mMapData->printMap();
}

void MazeMapper::handleRedDotRecognizedEvent(RedDotRecognizedEvent ev) {
    /*MazeGrid grid;
    grid.setRedDotFound();
    mMapData->setFrontMazeGrid(grid);*/

    mMapData->setMazeStatus('\0', '\0', '\0', 'R');

    cout << "- Red dot recognized." << endl;

    mMapData->printMap();
}

void MazeMapper::handleSignRecognizedEvent(SignRecognizedEvent ev) {
    /*MazeGrid grid;
    grid.setSignFound(ev.getSignType());
    mMapData->setCurrMazeGrid(grid);*/

    mMapData->setMazeStatus('\0', 'G', '\0', 'R');

    cout << "- Sign recognized." << endl;

    mMapData->printMap();
}

void MazeMapper::handleSquareRecognizedEvent(SquareRecognizedEvent ev) {
    /*MazeGrid grid;
    grid.setEndSquare();
    mMapData->setFrontMazeGrid(grid);*/

    mMapData->setMazeStatus('\0', '\0', '\0', 'E');

    cout << "- Square recognized." << endl;

    mMapData->printMap();
}
