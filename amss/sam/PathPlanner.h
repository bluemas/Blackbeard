/*
 * PathPlanner.h
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#ifndef SAM_PATHPLANNER_H_
#define SAM_PATHPLANNER_H_

#include <iostream>
#include <stack>
#include "../common/Constants.h"
#include "MapData.h"
#include "MazeMapper.h"

using namespace std;

struct MazeNode {
    MazeNode() {
        leftNode = frontNode = rightNode = parent = NULL;
        visited = false;
    }

    MazeNode* leftNode;
    MazeNode* frontNode;
    MazeNode* rightNode;
    MazeNode* parent;
    bool visited;
};

class PathPlanner {
public:
    PathPlanner();
    PathPlanner(MapData *mapData);
    virtual ~PathPlanner();

    void init();
    Direction nextDirection();

private:
    void initGraph();
    MazeNode* findBackTraceNode(MazeNode* node);
    MazeNode* getNextBackTraceNode(MazeNode* node);
    bool isMappedComplete();
    MazeNode* backTrackToDestNode(MazeNode* node);
    bool getNextBackTracingNode(MazeNode* destNode, MazeNode* currentNode,
                                MazeNode* nextNode, Direction& nextDirection);

    Direction getDirectionToBackTrace();
    int mCount = 0; // TEMP
    stack<Direction> mDirStack;
    MapData *mMapData;
    MazeNode* mGraph;
    MazeNode* mStartSquare;
    MazeNode* mParentNode;
    MazeNode* mCurrentNode;
    MazeNode* mBackTracingDestNode;
    MazeNode* mNextNode;
    bool mBackTracingMode;
    Direction mPrevNewDirection;
};

#endif /* SAM_PATHPLANNER_H_ */
