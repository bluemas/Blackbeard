/*
 * MazeGrid.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEGRID_H_
#define SAM_MAZEGRID_H_

#include <string>
#include "../common/Constants.h"

using namespace std;

class MazeGrid {

public:
    MazeGrid();
    virtual ~MazeGrid();

    void init();
    void setForwardWall(bool isWall);
    void setBackwardWall(bool isWall);
    void setLeftWall(bool isWall);
    void setRightWall(bool isWall);
    bool isForwardWall();
    bool isBackwardWall();
    bool isLeftWall();
    bool isRightWall();
    void setVisited();
    void setRedDot();
    void setSign(SignType signType, Direction dir);
    void setStartSquare();
    void setEndSquare();
    bool isVisited();
    bool isRedDot();
    bool isStartSquare();
    bool isEndSquare();
    SignType getSignType();
    Direction getSignDirection();

private:
    bool mVisited = false;
    bool mForwardWall = false;
    bool mLeftWall = false;
    bool mRightWall = false;
    bool mBackwardWall = false;
    bool mRedDotFound = false;
    SignType mSignType = SignType::SignNone;
    Direction mSignDirection = Direction::none;
    bool mStartSqureFound = false;
    bool mEndSqureFound = false;
};


#endif /* SAM_MAZEGRID_H_ */
