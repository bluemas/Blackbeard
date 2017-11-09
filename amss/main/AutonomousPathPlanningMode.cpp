///////////////////////////////////////////////////////////
//  AutonomousPathPlanningMode.cpp
//  Implementation of the Class AutonomousPathPlanningMode
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "AutonomousPathPlanningMode.h"
#include "MainController.h"

AutonomousPathPlanningMode::AutonomousPathPlanningMode(MainController* mainController) {
    mModeName = RobotMode::AutoPathPlanning;
    mMainController = mainController;
}

AutonomousPathPlanningMode::~AutonomousPathPlanningMode() {
}

void AutonomousPathPlanningMode::doEntryAction() {
    // Determine next direction
    Direction nextDirection = mMainController->pathPlanner()->nextDirection();

    if (nextDirection != none) {
        // If robot needed to turn left or right, go to cross before turning direction
        if (nextDirection == Direction::left || nextDirection == Direction::right)
            mMainController->behaviorExecutor()->gotoCross();

        // Move robot
        mMainController->behaviorExecutor()->move(nextDirection);

        // Transition to AutonomousMovingMode
        mMainController->setCurrentMode(RobotMode::AutoMoving);
    }
    else
        // In case of fail to determine next direction, transition to suspend mode
        mMainController->setCurrentMode(RobotMode::Suspend);
}


