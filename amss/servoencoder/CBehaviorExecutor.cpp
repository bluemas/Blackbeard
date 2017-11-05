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
	switch(dir){
	case forward:
		break;
	case left:
		mServoEncoder->setWheelSpeed(-6, 6);
		sleep(2);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case right:	
		mServoEncoder->setWheelSpeed(6, -6);
		sleep(2);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case backward:
		//nothing
		break;
	}
}

void CBehaviorExecutor::stop(void)
{
	mSpeed = 0;
	mServoEncoder->setWheelSpeed(mSpeed, mSpeed);
}

void CBehaviorExecutor::manualMove(Direction dir)
{
	switch(dir){
	case forward:
		break;
	case left:
		break;
	case right:
		break;
	case backward:
		break;
	}
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
	double correction, left, right;

	mPID.SetError(offset);

	correction = mPID.RunPID();			// compute PID correction
	left = BASESPEED - correction;		// compute left wheel speed
	right = BASESPEED + correction;		// compute right wheel speed

	mServoEncoder->setWheelSpeed(left, right);
}


