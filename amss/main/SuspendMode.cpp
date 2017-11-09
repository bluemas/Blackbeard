///////////////////////////////////////////////////////////
//  SuspendMode.cpp
//  Implementation of the Class SuspendMode
//  Created on:      31-10-2017 PM 7:55:17
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "SuspendMode.h"


SuspendMode::SuspendMode(MainController* mainController) {
    mModeName = RobotMode::Suspend;
    mMainController = mainController;
}

void SuspendMode::doEntryAction() {

}
