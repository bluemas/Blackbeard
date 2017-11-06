// PID Class Header File

#ifndef _CPID_H
#define _CPID_H

// Parameters for PID
#define KP        1.0               // defaut 1.0
#define KI        0.1               // defaut 0.1
#define KD        0.0               // defaut 0.0
#define BASESPEED 6.0               // Range 0-50
#define BASESPEEDFUDGEFACTOR 0.80   // default 1.25

class CPID {
private:
	double	mKp;					// proportional gain
	double	mKi;					// integral gain
	double	mKd;					// derivative gain

	double	mError;					// error in the setpoint
	double	mErrorTime;				// time of the error in the setpoint
	double	mBaseSpeed;				// base speed of the robot used to compute magnigfy the error based on the speed of the robot
	double	mLastError;				// previous error in the setpoint,
	long	mLastErrorTime;			// previous time of the previous error in the setpoint

	double	mIntegral;				// computed integral
	double	mDerivative;			// computed derivative
	double	mSpeedFudgeFactor;		// fudge factor correction used in conjuction with the robot base speed

public:
	CPID();
	~CPID();

	long getTimeMs(void);
	void initPID();
	void setError(double ErrorIn);
	void runPID();	
};

#endif

