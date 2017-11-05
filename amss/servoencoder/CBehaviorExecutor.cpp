// CBehaviorExecutor Class Source File

#include "CBehaviorExecutor.h"

CBehaviorExecutor:: CBehaviorExecutor() 
{
	mServoEncoder = CServoEncoder.getInstance();
	mPID = new CPID();

	mPID.InitPID(KP, KI, KD, BASESPEED, BASESPEEDFUDGEFACTOR);

	mPan = SERVO_CENTER_OR_STOP;
	mTilt = SERVO_CENTER_OR_STOP;
}

CBehaviorExecutor::~CBehaviorExecutor() {}

void CBehaviorExecutor::move(Direction dir)
{
	switch(dir){
	case forward:
		//nothing to do in autonomous.. just move forward in offset function
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
	mSpeed = MANUALSPEED;
	switch(dir){
	case forward:
		mServoEncoder->setWheelSpeed(mSpeed, mSpeed);
		break;
	case left:
		mServoEncoder->setWheelSpeed(-mSpeed, mSpeed);
		usleep(20000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case right:
		mServoEncoder->setWheelSpeed(mSpeed, -mSpeed);
		usleep(20000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case backward:
		// nothing
		break;
	}
}

void CBehaviorExecutor::gotoCross(void)
{
	mServoEncoder->setWheelSpeed(BASESPEED, BASESPEED);
	sleep(1);
	mServoEncoder->setWheelSpeed(0, 0);
}

void CBehaviorExecutor::panAndTitl(CamDirection dir)
{
	switch(dir) {
	case panleft:
		mPan--;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
		break;
	case panright:
		mPan++;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
		break;
	case tiltup:
		mTilt--;
		mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
		break;
	case tiltdown:
		mTilt++;
		mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
		break;
	}
}

void CBehaviorExecutor::setOffset(float offset)
{
	double correction, left, right;

	mPID.SetError(offset);
	
	correction = mPID.RunPID(); 		// compute PID correction
	left = BASESPEED - correction;		// compute left wheel speed
	right = BASESPEED + correction; 	// compute right wheel speed

	mServoEncoder->setWheelSpeed(left, right);	
}

void CBehaviorExecutor::searchSign(Direction dir)
{
	// call function by thread.
	switch(dir) {
	case forward:
		break;
	case left:
		break;
	case right:
		break;
	}
}

void CBehaviorExecutor::setCamDefaultTrackLine(void)
{
	mServoEncoder->setCameraServosLineTrackMode();
}


