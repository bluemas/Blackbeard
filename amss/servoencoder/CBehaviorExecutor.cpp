// CBehaviorExecutor Class Source File

#include "CBehaviorExecutor.h"

CBehaviorExecutor:: CBehaviorExecutor() 
{
	mServoEncoder = CServoEncoder::getInstance();
	mPID = new CPID();

	mPID->initPID(KP, KI, KD, BASESPEED, BASESPEEDFUDGEFACTOR);

	mPan = SERVO_CENTER_OR_STOP;
	mTilt = SERVO_CENTER_OR_STOP;
}

CBehaviorExecutor::~CBehaviorExecutor() {}

void CBehaviorExecutor::move(Direction dir)
{
	switch(dir){
		case Direction::forward:
		//nothing to do in autonomous.. just move forward in offset function
		break;
	case Direction::left:
		mServoEncoder->setWheelSpeed(-6, 6);
		sleep(2);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::right:
		mServoEncoder->setWheelSpeed(6, -6);
		sleep(2);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::backward:
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
	case Direction::forward:
		mServoEncoder->setWheelSpeed(mSpeed, mSpeed);
		break;
	case Direction::left:
		mServoEncoder->setWheelSpeed(-mSpeed, mSpeed);
		usleep(20000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::right:
		mServoEncoder->setWheelSpeed(mSpeed, -mSpeed);
		usleep(20000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::backward:
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

void CBehaviorExecutor::panAndTilt(CamDirection dir)
{
	switch(dir) {
	case CamDirection::panleft:
		mPan--;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
		break;
	case CamDirection::panright:
		mPan++;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
		break;
	case CamDirection::tiltup:
		mTilt--;
		mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
		break;
	case CamDirection::tiltdown:
		mTilt++;
		mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
		break;
	}
}

void CBehaviorExecutor::setOffset(float offset)
{
	double correction, left, right;

	mPID->setError(offset);
	
	correction = mPID->runPID(); 		// compute PID correction
	left = BASESPEED - correction;		// compute left wheel speed
	right = BASESPEED + correction; 	// compute right wheel speed

	mServoEncoder->setWheelSpeed(left, right);	
}

void CBehaviorExecutor::searchSign(Direction dir)
{
	// call function by thread.
	switch(dir) {
	case Direction::forward:
		break;
	case Direction::left:
		break;
	case Direction::right:
		break;
	}
}

void CBehaviorExecutor::setCamDefaultTrackLine(void)
{
	mServoEncoder->setCameraServosLineTrackMode();
}


