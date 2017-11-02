// CBehaviorExecutor Class Header File

#ifndef _CBEHAVIOREXECUTOR_H
#define _CBEHAVIOREXECUTOR_H

#include "CServoEncoder.h"
#include "CPID.h"
#include "Constants.h"

class CBehaviorExecutor {
private:
	int mPan;
	int mTilt;
	int mSpeed;
	CPID mPID;
	CServoEncoder * mServoEncoder;
	
public:
	BehaviorExecutor();
	~BehaviorExecutor();

	void move(Direction dir);
	void stop(void);
	void manualMove(Direction dir);
	void gotoCross(void);
	void pan(void);
	void tilt(void);
	void setOffset(float offset);

};
#endif // _CBEHAVIOREXECUTOR_H
