// Sonar Sensor Class Source File

#include "CSonarFront.h"

CSonarFront::CSonarFront() {}
CSonarFront::~CSonarFront() {}
CSonarFront* CSonarFront::getInstance()
{
	if(mSonar == NULL)
	{
		mSonar = new CsonarFront();
		return mSonar;
	}
	else
	{
		return mSonar;
	}
}

void CSonarFront::init(int _trigger, int _echo)
{
	mTrigger = _trigger;
	mEcho = _echo;
	pinMode(mTrigger, OUTPUT);
	pinMOde(mEcho, INPUT);
	digitalWrite(mTrigger, LOW);
	delay(500);
}

double CsonarFront::getDistance(int timeout)
{
	long startTimeUsec,endTimeUsec,travelTimeUsec,timeoutstart;
	double distanceCm;

    if ((mTrigger==-1) || (mEcho==-1)) return(-1.0);
    
    delay(10);
    digitalWrite(mTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(mTrigger, LOW);

    timeoutstart=micros();

    while (digitalRead(mEcho) == LOW)
	{
    	if ( micros()-timeoutstart>=timeout) return (-1.0);
    }
    startTimeUsec = micros();
    while ( digitalRead(mEcho) == HIGH )
    {
    	endTimeUsec = micros();
        if (endTimeUsec-timeoutstart>=timeout) return (-1.0);
    }

    travelTimeUsec = endTimeUsec - startTimeUsec;
    distanceCm = travelTimeUsec/58.0;

    return distanceCm;
}

