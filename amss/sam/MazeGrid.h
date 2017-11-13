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

    const int WALL_NONE = 0;
    const int WALL_FRONT = 1;
    const int WALL_LEFT = 2;
    const int WALL_RIGHT = 4;
    const int WALL_BACK = 8;

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
