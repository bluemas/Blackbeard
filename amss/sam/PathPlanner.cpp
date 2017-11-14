/*
 * PathPlanner.cpp
 *
 *  Created on: 2017. 10. 31.
 *      Author: gtlove
 */

#include "../sam/PathPlanner.h"
#include "MazeMapper.h"
#include "../common/Logging.h"

PathPlanner::PathPlanner(MapData *mapData) {
    mMapData = mapData;
    init();
}

PathPlanner::~PathPlanner() {

}

void PathPlanner::init() {
    mMapData->init();

    initGraph();

    mCount = 0; // TODO remove
}

void PathPlanner::initGraph() {
    mStartSquare = new MazeNode();
    mBackTracingMode = false;
    mBackTracingDestNode = NULL;
}

Direction PathPlanner::nextDirection() {
    MazeNode* currentNode = mNextNode == NULL ? mStartSquare : mNextNode;
    Direction newDirection = Direction::none;
    
    if (!mBackTracingMode) {
        Logging::logOutput(Logging::DEBUG, "Possible direction : %d%d%d",
                           mMapData->isLeftAvailable(),
                           mMapData->isForwardAvailable(),
                           mMapData->isLeftAvailable());

        bool foundDirection = false;
        if (!currentNode->visited)
            currentNode->visited = true;

        if (mMapData->isLeftAvailable()) {
            if (currentNode->leftNode == NULL)
                currentNode->leftNode = new MazeNode();

            if (!currentNode->leftNode->visited) {
                currentNode->leftNode->parent = currentNode;
                mNextNode = currentNode->leftNode;
                newDirection = Direction::left;
                foundDirection = true;
            }
        }
        if (mMapData->isForwardAvailable() && !foundDirection) {
            if (currentNode->frontNode == NULL)
               currentNode->frontNode = new MazeNode();

            if (!currentNode->frontNode->visited) {
                currentNode->frontNode->parent = currentNode;
                mNextNode = currentNode->frontNode;
                newDirection = Direction::forward;
                foundDirection = true;
            }
        }
        if (mMapData->isRightAvailable() && !foundDirection) {
            if (currentNode->rightNode == NULL)
               currentNode->rightNode = new MazeNode();

            if (!currentNode->rightNode->visited) {
                currentNode->rightNode->parent = currentNode;
                mNextNode = currentNode->rightNode;
                newDirection = Direction::right;
                foundDirection = true;
            }
        }

        // In case of not being able to determine new direction
        if (!foundDirection && !mMapData->isLeftAvailable() &&
            !mMapData->isForwardAvailable() && !mMapData->isRightAvailable()) {

            mBackTracingMode = true;

            // Find node to back trace
            mBackTracingDestNode = backTrackToDestNode(currentNode);
            // TODO : mBackTracingDestNode�� NULL ��� ó��

            // Get next back tracing node and direction
            getNextBackTracingNode(mBackTracingDestNode, currentNode, mNextNode,
                                   newDirection);
        }
        else {
            mBackTracingMode = false;
            mBackTracingDestNode = NULL;
            Logging::logOutput(Logging::INFO, "PathPlanner Direction Output = %s",
                               newDirection == Direction::left ? "LEFT" :
                               (newDirection == Direction::forward ? "FRONT" :
                                (newDirection == Direction::right ? "RIGHT" : "UNKNOWN")));
        }
    }
    else {
        // If current node is back tracing destination node, determine next new direction
        if (mBackTracingDestNode == mNextNode) {
            mBackTracingMode = false;
            mBackTracingDestNode = NULL;
            newDirection = nextDirection();
        }
        else {
            // Get next back tracing node and direction
            getNextBackTracingNode(mBackTracingDestNode, currentNode, mNextNode,
                                   newDirection);
        }
    }

    return newDirection;
}

bool PathPlanner::getNextBackTracingNode(MazeNode* destNode, MazeNode* currentNode,
                                         MazeNode* nextNode, Direction& nextDirection) {
    bool match = false;
    MazeNode* node = destNode;
    if (node != currentNode) {
        if (node->leftNode && node->leftNode->visited) {
            match = getNextBackTracingNode(destNode, node->leftNode, nextNode,
                                           nextDirection);
            if (match)
                nextNode = node->leftNode;
        }
        if (!match && node->frontNode && node->frontNode->visited) {
            match = getNextBackTracingNode(destNode, node->frontNode, nextNode,
                                           nextDirection);
            if (match)
                nextNode = node->frontNode;
        }
        if (!match && node->rightNode && node->rightNode->visited) {
            match = getNextBackTracingNode(destNode, node->rightNode, nextNode,
                                           nextDirection);
            if (match)
                nextNode = node->rightNode;
        }
    }
    else {
        match = true;
    }

    if (!match) {
        nextNode = NULL;
        nextDirection = Direction::none;
    }

    return match;
}

MazeNode* PathPlanner::backTrackToDestNode(MazeNode* node) {
    MazeNode* parentNode = node->parent;
    while (parentNode != NULL) {
        if (parentNode->leftNode && parentNode->leftNode->visited) {
            if ((parentNode->frontNode && !parentNode->frontNode->visited) ||
                (parentNode->rightNode && !parentNode->rightNode->visited)) {
                break;
            }
        }
        else if (parentNode->frontNode && parentNode->frontNode->visited) {
            if ((parentNode->leftNode && !parentNode->leftNode->visited) ||
                (parentNode->rightNode && !parentNode->rightNode->visited)) {
                break;
            }
        }
        else if (parentNode->rightNode && parentNode->rightNode->visited) {
            if ((parentNode->leftNode && !parentNode->leftNode->visited) ||
                (parentNode->frontNode && !parentNode->frontNode->visited)) {
                break;
            }
        }
        else
            parentNode = parentNode->parent;
    }
    return parentNode;
}

#if 0
Direction PathPlanner::nextDirection() {
    Direction dir = Direction::none;

    // Return previous direction if the mode is back tracking
    if (mMapData->isBackTrackingMode() && !mDirStack.empty()) {
        dir = mDirStack.top();
        mDirStack.pop();
        return dir;
    }

    // Find next direction by the left hand rule
    if (mMapData->isLeftAvailable()) {
        dir = Direction::left;
    } else if (mMapData->isForwardAvailable()) {
        dir = Direction::forward;
    } else if (mMapData->isRightAvailable()) {
        dir = Direction::right;
    } else if (isMappedComplete()){
        return Direction::none;
    } else {
        // No way to go.
        return Direction::backward;
    }

    // Push a direction to the stack for back tracking
    if (!mMapData->isBackTrackingMode()) {
        mDirStack.push(dir);
    }

    // TEST CODE!!!
    if (mCount == 0) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 1) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 2) {
        cout << "Move right in PathPlanning" << endl;
        dir = Direction::right;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 3) {
        cout << "Move front in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 4) {
        cout << "Move right in PathPlanning" << endl;
        dir = Direction::right;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 5) {
        cout << "Move right in PathPlanning" << endl;
        dir = Direction::right;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 6) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 7) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 8) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 9) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 10) {
        cout << "Move forward in PathPlanning" << endl;
        dir = Direction::forward;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 11) {
        cout << "Move left in PathPlanning" << endl;
        dir = Direction::left;
        mMapData->setNextDirection(dir);
        mCount++;
    } else if (mCount == 12) {
        cout << "Move none in PathPlanning" << endl;
        dir = Direction::none;
        mMapData->setNextDirection(dir);
        mCount++;
    }

    return dir;
}
#endif

bool PathPlanner::isMappedComplete() {
    // TODO Check whether a maze is mapped completely
    return false;
}
