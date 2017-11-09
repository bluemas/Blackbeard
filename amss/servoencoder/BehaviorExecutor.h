// BehaviorExecutor Class Header File

#ifndef _BEHAVIOREXECUTOR_H
#define _BEHAVIOREXECUTOR_H

#include <unistd.h>
#include <pthread.h>
#include "ServoEncoder.h"
#include "../common/Constants.h"
#include "PID.h"
#include "../common/Constants.h"

#define MANUALSPEED	10
#define CAMSEARCHOFFSET 10

class BehaviorExecutor {
private:
	int mPan;
	int mTilt;
	int mSpeed;
	PID* mPID;
	ServoEncoder* mServoEncoder;
	pthread_t mThreadSign;
	pthread_t mThreadPanTilt;
	Direction mSearchDir;
	CamDirection mCamDir;

	static void* runSign(void* ptr);
	static void* runPanTilt(void* ptr);
	void searchSignDir(void);
	void panAndTiltDir(void);

public:
	BehaviorExecutor();
	~BehaviorExecutor();

	void move(Direction dir);
	void stop(void);
	void manualMove(Direction dir);
	void gotoCross(void);
	void panAndTilt(CamDirection dir);
	void stopPanAndTilt(void);
	void setOffset(float offset);
	void searchSign(Direction dir);
	void stopSign(void);
	void setCamDefaultTrackLine(void);
	void setCamDefault(void);
	
};

#endif // _BEHAVIOREXECUTOR_H
