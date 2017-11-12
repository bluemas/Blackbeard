/*
 * MazeMapper.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_MAZEMAPPER_H_
#define SAM_MAZEMAPPER_H_

#include <iostream>
#include <atomic>
#include "../common/Constants.h"
#include "../common/event/WallSensingEventHandler.h"
#include "../common/event/RedDotRecognizedEventHandler.h"
#include "../common/event/SignRecognizedEventHandler.h"
#include "../common/event/SquareRecognizedEventHandler.h"
#include "MapData.h"

using namespace std;

class MazeMapper :
        public WallSensingEventHandler,
        public RedDotRecognizedEventHandler,
        public SignRecognizedEventHandler,
        public SquareRecognizedEventHandler {

public:
    MazeMapper(MapData *mapData);
    virtual ~MazeMapper();

    void handleWallSensingEvent(WallSensingEvent ev);
    void handleRedDotRecognizedEvent(RedDotRecognizedEvent ev);
    void handleSignRecognizedEvent(SignRecognizedEvent ev);
    void handleSquareRecognizedEvent(SquareRecognizedEvent ev);

private:
    static const int NO_SENSING              = 0;
    static const int WALL_SENSING_ENABLE     = 1;
    static const int REDDOT_SENSING_ENABLE   = 2;
    static const int SIGN_RECOGNIZED_ENABLE  = 4;
    static const int CROSS_RECOGNIZED_ENABLE = 8;

    MapData *mMapData;
    int mStatus;

    bool mPrevLeftWall = false;
    bool mPrevRightWall = false;

    // ���� ���� : WALL, RED DOT, CROSS => initial value
    // ���� wall �ν� ���� : RED DOT, CROSS
    // cross �ν� ���� :
    // dot �ν� ���� : SIGN
    // sign �ν� ���� :

    /* ���� ���� �� WALL detect
     * AUTO MOVING �� WALL, CROSS, DOT
     *     WALL open �� ���� ���� ����ĭ�� ���
     *     CROSS ������ �� ���� ���� ����ĭ���� ����ĭ �̵�
     *     DOT ������ �� ���� ���� ����ĭ�� RED DOT ���
     */
};

#endif /* SAM_MAZEMAPPER_H_ */
