// BehaviorExecutor Class Header File

#ifndef _BEHAVIOREXECUTOR_H
#define _BEHAVIOREXECUTOR_H

#include <unistd.h>
#include <pthread.h>
#include "ServoEncoder.h"
#include "PID.h"
#include "../common/Constants.h"

#define MANUALSPEED	10

class BehaviorExecutor {
private:
	int mPan;
	int mTilt;
	int mSpeed;
	PID* mPID;
	ServoEncoder* mServoEncoder;

public:
	BehaviorExecutor();
	~BehaviorExecutor();

	void move(Direction dir);
	void stop(void);
	void manualMove(Direction dir);
	void gotoCross(void);
	void panAndTilt(CamDirection dir);
	void setOffset(float offset);
	void searchSign(Direction dir);
	void setCamDefaultTrackLine(void);
	
};

#endif // _BEHAVIOREXECUTOR_H
