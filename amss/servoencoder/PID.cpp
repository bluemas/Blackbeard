// CPID Class Source File

#include <time.h>
#include <math.h>
#include <inttypes.h> 
#include "PID.h"

CPID::CPID() {}
CPID::~CPID() {}

//-----------------------------------------------------------------
// GetTimeMs returns the current time in miliseconds
//-----------------------------------------------------------------
long CPID::GetTimeMs(void)
{
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    return((intmax_t)s*1000+ms);
}

//-----------------------------------------------------------------
// Init_PID Initializes the Proportional Integral Derivative(PID)
// Controller with desired constants
//-----------------------------------------------------------------
void CPID::InitPID(double Kpi, double Kii, double Kdi,double BaseSpeedi, double SpeedFudgeFactori) 
{
	mErrorTime = GetTimeMs();
	mKp = Kpi;
	mKi = Kii;
	mKd = Kdi;

	mError = 0;
	mBaseSpeed = BaseSpeedi;
	mSpeedFudgeFactor = SpeedFudgeFactori;
	mLastError = 0.0;
	mIntegral = 0.0;
	mDerivative = 0.0;
}

//-----------------------------------------------------------------
// SetError Set the PIDS current calculated errror from desired
// direction 
//-----------------------------------------------------------------
void CPID::SetError(double ErrorIn)
{
	mError = (mBaseSpeed / mSpeedFudgeFactor) * ErrorIn;
	mLastErrorTime =  mErrorTime;
	mErrorTime = GetTimeMs();
}

//-----------------------------------------------------------------
// RunPID calculates the corrected direction, returens the
// corrrected direction
//-----------------------------------------------------------------
double CPID::RunPID(void) 
{
	long iterationTime = (long) (mErrorTime - mLastErrorTime);

	mIntegral = (mError / iterationTime) + mIntegral;

	mDerivative = (mError - mLastError) / iterationTime;

	double correction = mKp * mError + mKi * mIntegral + mKd * mDerivative;

	mLastError = mError;

	return(correction);
}

