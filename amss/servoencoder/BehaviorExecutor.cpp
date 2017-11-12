// BehaviorExecutor Class Source File

#include "BehaviorExecutor.h"

BehaviorExecutor:: BehaviorExecutor() 
{
	mServoEncoder = ServoEncoder::getInstance();
	mPID = new PID();

	mPID->initPID(KP, KI, KD, BASESPEED, BASESPEEDFUDGEFACTOR);

	mPan = SERVO_CENTER_OR_STOP;
	mTilt = SERVO_CENTER_OR_STOP;

	mServoEncoder->openServos();
}

BehaviorExecutor::~BehaviorExecutor() {}

void BehaviorExecutor::move(Direction dir)
{
	switch(dir){
		case Direction::forward:
		//nothing to do in autonomous.. just move forward in offset function
		mServoEncoder->setWheelSpeed(BASESPEED, BASESPEED);
		break;
	case Direction::left:
		printf("Left turn\n");
		mServoEncoder->setWheelSpeed(-BASESPEED, BASESPEED);
		usleep(950000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::right:
		printf("Right turn\n");
		mServoEncoder->setWheelSpeed(BASESPEED, -BASESPEED);
		usleep(850000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::backward:
		printf("Backward \n");
		mServoEncoder->setWheelSpeed(-BASESPEED, BASESPEED);
		usleep(1850000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	default:
		break;
	}
}

void BehaviorExecutor::stop(void)
{
	mSpeed = 0;
	mServoEncoder->setWheelSpeed(mSpeed, mSpeed);
	
	pthread_cancel(mThreadMove);
}

void* BehaviorExecutor::runManualMove(void* ptr)
{
	((BehaviorExecutor*)ptr)->manualMoveDir();
	return ptr;
}

void BehaviorExecutor::manualMoveDir(void)
{
	mSpeed = MANUALSPEED;
	while(1)
	{
		switch(mMoveDir){
		case Direction::forward:
			printf("Forward\n");
			mServoEncoder->setWheelSpeed(mSpeed, mSpeed);
			break;
		case Direction::left:
			printf("Left turn\n");
			mServoEncoder->setWheelSpeed(-mSpeed, mSpeed);
			break;
		case Direction::right:
			printf("Right turn\n");
			mServoEncoder->setWheelSpeed(mSpeed, -mSpeed);
			break;
		case Direction::backward:
			// nothing
			break;
		default:
			break;
		}
		sleep(1);
	}

}


void BehaviorExecutor::manualMove(Direction dir)
{
	mMoveDir = dir;

	pthread_create(&mThreadMove, NULL, &BehaviorExecutor::runManualMove, (void*)this);
}

void BehaviorExecutor::gotoCross(void)
{
	mServoEncoder->setWheelSpeed(BASESPEED, BASESPEED);
	usleep(1050000);
	mServoEncoder->setWheelSpeed(0, 0);
}

void* BehaviorExecutor::runPanTilt(void* ptr)
{
	((BehaviorExecutor*)ptr)->panAndTiltDir();
	return ptr;
}

void BehaviorExecutor::panAndTiltDir(void)
{
	while(1)
	{
		switch(mCamDir) {
		case CamDirection::panleft:
			mPan < PAN_CAMERA_MAX ? mPan++ : mPan = PAN_CAMERA_MAX;
			mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
			break;
		case CamDirection::panright:
			mPan > PAN_CAMERA_MIN ? mPan-- : mPan = PAN_CAMERA_MIN; 
			mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
			break;
		case CamDirection::tiltup:
			mTilt > TILT_CAMERA_MIN ? mTilt-- : mTilt = TILT_CAMERA_MIN;
			mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
			break;
		case CamDirection::tiltdown:
			mTilt++;
			mTilt < TILT_CAMERA_MAX ? mTilt++ : mTilt = TILT_CAMERA_MAX;
			mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
			break;
		default:
			break;
		}

		usleep(100000);
	}

}

void BehaviorExecutor::panAndTilt(CamDirection dir)
{
	mCamDir = dir;

	pthread_create(&mThreadPanTilt, NULL, &BehaviorExecutor::runPanTilt, (void*)this);
}

void BehaviorExecutor::stopPanAndTilt(void)
{
	pthread_cancel(mThreadPanTilt);
}

void BehaviorExecutor::setOffset(float offset)
{
	double correction, left, right;

	mPID->setError(offset);
	
	correction = mPID->runPID(); 		// compute PID correction
	left = BASESPEED - correction;		// compute left wheel speed
	right = BASESPEED + correction; 	// compute right wheel speed

	mServoEncoder->setWheelSpeed(left, right);	
}

void* BehaviorExecutor::runSign(void * ptr)
{
	((BehaviorExecutor*)ptr)->searchSignDir();
	return ptr;
}

void BehaviorExecutor::searchSignDir(void)
{
	int searchCnt = 0;
	int check = 0;
	int tiltPos = 0;
	
	mTilt = SERVO_CENTER_OR_STOP;
	check = CAMSEARCHOFFSET * 2;
	
	switch(mSearchDir) {
	case Direction::forward:
		mPan = SERVO_CENTER_OR_STOP;
		break;
	case Direction::right:
		mPan = PAN_CAMERA_MIN;
		break;
	case Direction::left:
		mPan = PAN_CAMERA_MAX;
		break;
	default:
		mPan = SERVO_CENTER_OR_STOP;
		break;
	}

	// Search Sign Direction
	mServoEncoder->setServoPosition(CAMERA_PAN, mPan);

	tiltPos = mTilt - CAMSEARCHOFFSET;
	for(searchCnt = 0; searchCnt < check; searchCnt++)
	{
		mServoEncoder->setServoPosition(CAMERA_TILT, tiltPos);
		tiltPos++;
		usleep(200000);
	}

	if(mSearchDir != Direction::right)
	{
		tiltPos = mTilt-CAMSEARCHOFFSET;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan-CAMSEARCHOFFSET);
		for(searchCnt = 0 ; searchCnt < check; searchCnt++)
		{
			mServoEncoder->setServoPosition(CAMERA_TILT, tiltPos);
			tiltPos++;
			usleep(200000);
		}
	}

	if(mSearchDir != Direction::left)
	{
		tiltPos = mTilt-CAMSEARCHOFFSET;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan+CAMSEARCHOFFSET);
		for(searchCnt = 0 ; searchCnt < check; searchCnt++)
		{
			mServoEncoder->setServoPosition(CAMERA_TILT, tiltPos);
			tiltPos++;
			usleep(200000);
		}
	}
	pthread_join(mThreadSign, NULL);
}

void BehaviorExecutor::searchSign(Direction dir)
{
	// Save Search direction
	mSearchDir = dir;

	pthread_create(&mThreadSign, NULL, &BehaviorExecutor::runSign, (void*)this);
}

void BehaviorExecutor::stopSign(void)
{	
	pthread_cancel(mThreadSign);
	setCamDefaultTrackLine();
}

void BehaviorExecutor::setCamDefaultTrackLine(void)
{	
	mPan = TRK_LINE_CAM_PAN;
	mTilt = TRK_LINE_CAM_TILT;
	
	mServoEncoder->setCameraServosLineTrackMode();
}

void BehaviorExecutor::setCamDefault(void)
{
	mPan = SERVO_CENTER_OR_STOP;
	mTilt = SERVO_CENTER_OR_STOP;
	
	mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
	mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
	
}


