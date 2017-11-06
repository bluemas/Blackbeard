// CBehaviorExecutor Class Header File

#ifndef _CBEHAVIOREXECUTOR_H
#define _CBEHAVIOREXECUTOR_H

#include <unistd.h>
//#include <thread.h>
#include "CServoEncoder.h"
#include "CPID.h"
#include "..\common\Constants.h"

#define MANUALSPEED	20


class CBehaviorExecutor {
private:
	int mPan;
	int mTilt;
	int mSpeed;
	CPID* mPID;
	CServoEncoder * mServoEncoder;
	
public:
	CBehaviorExecutor();
	~CBehaviorExecutor();

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
