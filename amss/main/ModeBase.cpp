///////////////////////////////////////////////////////////
//  ModeBase.cpp
//  Implementation of the Class ModeBase
//  Created on:      31-10-2017 PM 7:55:16
//  Original author: bluemas
///////////////////////////////////////////////////////////

#include "ModeBase.h"


ModeBase::ModeBase(){

}

ModeBase::~ModeBase(){

}

RobotMode ModeBase::getModeName() {
    return mModeName;
}

char ModeBase::getModeNameChar() {
    char mode;
    switch (mModeName) {
        case RobotMode::Manual:
            mode = 'M';
            break;
        case RobotMode::AutoPathPlanning:
        case RobotMode::AutoMoving:
        case RobotMode::AutoSignRecognition:
            mode = 'A';
            break;
        case RobotMode::Suspend:
            mode = 'S';
            break;
    }
    return mode;
}
