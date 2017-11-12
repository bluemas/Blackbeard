/*
 * MazeGrid.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEGRID_H_
#define SAM_MAZEGRID_H_

#include "../common/Constants.h"

class MazeGrid {

    const int WALL_TOP = 1;
    const int WALL_RIGHT = 2;
    const int WALL_BOTTOM = 4;
    const int WALL_LEFT = 8;

    const int WALL_NONE = 0;
    const int WALL_ALL = WALL_TOP | WALL_RIGHT | WALL_BOTTOM | WALL_LEFT;

public:
    MazeGrid();
    virtual ~MazeGrid();

    void setRedDotFound();
    void setSignFound(SignType signType);
    void setEndSquare();

private:
    int mWallStatus = WALL_NONE;
    bool mRedDotFound = false;
    SignType mSignType = SignType::SignNone;
    bool mEndSqureFound = false;
};


#endif /* SAM_MAZEGRID_H_ */
