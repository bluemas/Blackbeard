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

void BehaviorExecutor::stop(void)
{
	mSpeed = 0;
	mServoEncoder->setWheelSpeed(mSpeed, mSpeed);
}

void BehaviorExecutor::manualMove(Direction dir)
{
	mSpeed = MANUALSPEED;
	switch(dir){
	case Direction::forward:
		printf("Forward\n");
		mServoEncoder->setWheelSpeed(mSpeed, mSpeed);
		break;
	case Direction::left:
		printf("Left turn\n");
		mServoEncoder->setWheelSpeed(-mSpeed, mSpeed);
		usleep(800000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::right:
		printf("Right turn\n");
		mServoEncoder->setWheelSpeed(mSpeed, -mSpeed);
		usleep(800000);
		mServoEncoder->setWheelSpeed(0, 0);
		break;
	case Direction::backward:
		// nothing
		break;
	}
}

void BehaviorExecutor::gotoCross(void)
{
	mServoEncoder->setWheelSpeed(BASESPEED, BASESPEED);
	sleep(1);
	mServoEncoder->setWheelSpeed(0, 0);
}

void BehaviorExecutor::panAndTilt(CamDirection dir)
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

void BehaviorExecutor::setOffset(float offset)
{
	double correction, left, right;

	mPID->setError(offset);
	
	correction = mPID->runPID(); 		// compute PID correction
	left = BASESPEED - correction;		// compute left wheel speed
	right = BASESPEED + correction; 	// compute right wheel speed

	mServoEncoder->setWheelSpeed(left, right);	
}

void* BehaviorExecutor::run(void * ptr)
{
	((BehaviorExecutor*)ptr)->searchSignDir();
}

void BehaviorExecutor::searchSignDir(void)
{
	int searchCnt = 0;
	mTilt = SERVO_CENTER_OR_STOP;

	switch(mSearchDir) {
	case Direction::forward:
		mPan = SERVO_CENTER_OR_STOP;
		break;
	case Direction::left:
		mPan = PAN_CAMERA_MIN;
		break;
	case Direction::right:
		mPan = PAN_CAMERA_MAX;
		break;
	}

	printf("SearchSign DIR!!\n");
	mServoEncoder->setServoPosition(CAMERA_PAN, mPan);
	mServoEncoder->setServoPosition(CAMERA_TILT, mTilt);
	usleep(200000);

	mServoEncoder->setServoPosition(CAMERA_TILT, mTilt-CAMSEARCHOFFSET);
	usleep(200000);
	printf("SearchSign DIR!! - Center + UP\n");
	mServoEncoder->setServoPosition(CAMERA_TILT, mTilt+CAMSEARCHOFFSET);
	usleep(200000);
	printf("SearchSign DIR!! - Center + DOWN\n");

	if(mSearchDir != Direction::left)
	{
		printf("SearchSign DIR!! - Right \n");
		int tiltPos = mTilt-CAMSEARCHOFFSET;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan-CAMSEARCHOFFSET);
		for(searchCnt = 0 ; searchCnt < 3; searchCnt++)
		{
			mServoEncoder->setServoPosition(CAMERA_TILT, tiltPos);
			tiltPos = tiltPos + CAMSEARCHOFFSET;
			usleep(200000);
		}
	}

	if(mSearchDir != Direction::right)
	{
		printf("SearchSign DIR!! - Left \n");
		int tiltPos = mTilt-CAMSEARCHOFFSET;
		mServoEncoder->setServoPosition(CAMERA_PAN, mPan+CAMSEARCHOFFSET);
		for(searchCnt = 0 ; searchCnt < 3; searchCnt++)
		{
			mServoEncoder->setServoPosition(CAMERA_TILT, tiltPos);
			tiltPos = tiltPos + CAMSEARCHOFFSET;
			usleep(200000);
		}
	}
	pthread_join(mThread, NULL);
}

void BehaviorExecutor::searchSign(Direction dir)
{
	// Save Search direction
	mSearchDir = dir;

	pthread_create(&mThread, NULL, &BehaviorExecutor::run, (void*)this);
}

void BehaviorExecutor::setCamDefaultTrackLine(void)
{	
	mPan = TRK_LINE_CAM_PAN;
	mTilt = TRK_LINE_CAM_TILT;
	
	mServoEncoder->setCameraServosLineTrackMode();
}


