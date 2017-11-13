///////////////////////////////////////////////////////////
//  AutonomousPathPlanningMode.cpp
//  Implementation of the Class AutonomousPathPlanningMode
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "AutonomousPathPlanningMode.h"
#include "MainController.h"
#include "../common/Logging.h"

AutonomousPathPlanningMode::AutonomousPathPlanningMode(
        MainController* mainController) {
    mModeName = RobotMode::AutoPathPlanning;
    mMainController = mainController;
}

void AutonomousPathPlanningMode::doEntryAction() {
    // Determine next direction
    Direction nextDirection = mMainController->pathPlanner()->nextDirection();

    Logging::logOutput(Logging::INFO, "Next direction is %s.",
                       nextDirection == Direction::forward ? "Forward" :
                       (nextDirection == Direction::left ? "Left" :
                        (nextDirection == Direction::right ? "Right" :
                         (nextDirection == Direction::forward ? "Backward" :
                          "None"))));

    if (nextDirection != Direction::none) {
        // If robot needed to turn left or right, go to cross before turning direction
        if (nextDirection == Direction::left ||
            nextDirection == Direction::right) {

            Logging::logOutput(Logging::INFO, "Moving to cross line");

            mMainController->behaviorExecutor()->gotoCross();
        }

        // Move robot
        mMainController->ignoreCrossDetection(true);
        mMainController->behaviorExecutor()->move(nextDirection);
        mMainController->ignoreCrossDetection(false);

        // Transition to AutonomousMovingMode
        mMainController->setCurrentMode(RobotMode::AutoMoving);
    }
    else {
        // In case of fail to determine next direction, transition to suspend mode
        mMainController->networkManager()->send(NetworkMsg::MazeSovlingCompleted,
                                                0, NULL);
        mMainController->setCurrentMode(RobotMode::Manual);

        Logging::logOutput(Logging::ERROR, "Finished solving a maze.");
    }
}

void AutonomousPathPlanningMode::handleCollisionEvent(WallCollisionEvent ev) {
    if (ev.isWarnCollision()) {
        char warning[256] = "E/Robot is about to hit the wall.";
        mMainController->networkManager()->send(NetworkMsg::RobotStatusMessage,
                                                strlen(warning), warning);
    }
}


