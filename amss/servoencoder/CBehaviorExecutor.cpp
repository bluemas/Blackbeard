// CBehaviorExecutor Class Source File

#include "CBehaviorExecutor.h"

CBehaviorExecutor:: CBehaviorExecutor() 
{
	mServoEncoder = CServoEncoder.getInstance();
	mPID = new CPID();

	mPID.InitPID(KP, KI, KD, BASESPEED, BASESPEEDFUDGEFACTOR);
}

CBehaviorExecutor::~CBehaviorExecutor() {}

void CBehaviorExecutor::move(Direction dir)
{
	// move forward --> PID offset processing~!!
}

void CBehaviorExecutor::stop(void)
{

}

void CBehaviorExecutor::manualMove(Direction dir)
{

}

void CBehaviorExecutor::gotoCross(void)
{

}

void CBehaviorExecutor::pan(void)
{

}

void CBehaviorExecutor::tilt(void)
{
	
}

void CBehaviorExecutor::setOffset(float offset)
{
	mPID.SetError(offset);
}


