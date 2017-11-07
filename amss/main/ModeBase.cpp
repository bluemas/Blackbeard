///////////////////////////////////////////////////////////
//  ModeBase.cpp
//  Implementation of the Class ModeBase
//  Created on:      31-10-2017 PM 7:55:16
//  Original author: bluem
///////////////////////////////////////////////////////////

#include "ModeBase.h"


ModeBase::ModeBase(){

}



ModeBase::~ModeBase(){

}

ModeBase* ModeBase::getCurrentMode() {
    if (this)
        return this;
    else
        return nullptr;
}
