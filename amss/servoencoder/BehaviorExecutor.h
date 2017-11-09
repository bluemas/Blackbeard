// BehaviorExecutor Class Header File

#ifndef _BEHAVIOREXECUTOR_H
#define _BEHAVIOREXECUTOR_H

#include <unistd.h>
#include <pthread.h>
#include "ServoEncoder.h"
#include "../common/Constants.h"
#include "PID.h"

#define MANUALSPEED	20

enum CamDirection {
	panleft = 0,
	panright,
	tiltup,
	tiltdown
};

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
