// PID Class Source File

#include <time.h>
#include <math.h>
#include <inttypes.h> 
#include "PID.h"

PID::PID() {}
PID::~PID() {}

//-----------------------------------------------------------------
// GetTimeMs returns the current time in miliseconds
//-----------------------------------------------------------------
long PID::getTimeMs(void)
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
void PID::initPID(double Kpi, double Kii, double Kdi, double BaseSpeedi, double SpeedFudgeFactori) 
{
	mErrorTime = getTimeMs();
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
void PID::setError(double ErrorIn)
{
	mError = (mBaseSpeed / mSpeedFudgeFactor) * ErrorIn;
	mLastErrorTime =  mErrorTime;
	mErrorTime = getTimeMs();
}

//-----------------------------------------------------------------
// RunPID calculates the corrected direction, returens the
// corrrected direction
//-----------------------------------------------------------------
double PID::runPID(void) 
{
	long iterationTime = (long) (mErrorTime - mLastErrorTime);

	mIntegral = (mError / iterationTime) + mIntegral;

	mDerivative = (mError - mLastError) / iterationTime;

	double correction = mKp * mError + mKi * mIntegral + mKd * mDerivative;

	mLastError = mError;

	return(correction);
}

