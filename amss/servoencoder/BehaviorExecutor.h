// CBehaviorExecutor Class Header File

#ifndef _CBEHAVIOREXECUTOR_H
#define _CBEHAVIOREXECUTOR_H

#include <unistd.h>
#include <thread.h>
#include "ServoEncoder.h"
#include "PID.h"
#include "Constants.h"

#define MANUALSPEED	20

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
	void panAndTilt(CamDirection dir);
	void setOffset(float offset);
	void searchSign(Direction dir);
	void setCamDefaultTrackLine(void);

};
#endif // _CBEHAVIOREXECUTOR_H
