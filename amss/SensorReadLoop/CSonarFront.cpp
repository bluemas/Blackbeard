// Sonar Sensor Class Source File

#include "CSonarFront.h"

CSonarFront::CSonarFront()
{
	mData = CSensorData.getInstance();
}

CSonarFront::~CSonarFront() {}

CSonarFront* CSonarFront::getInstance()
{
	if(mSonar == NULL)
	{
		mSonar = new CSonarFront();
		return mSonar;
	}
	else
	{
		return mSonar;
	}
}

void CSonarFront::init(void)
{
	mTrigger = PIN_NUM_TRIGGER;
	mEcho = PIN_NUM_ECHO;
	pinMode(mTrigger, OUTPUT);
	pinMOde(mEcho, INPUT);
	digitalWrite(mTrigger, LOW);
	delay(500);
}

void CSonarFront::start(void)
{
	int ret;

	ret = pthread_create(&mThread, NULL, &CSonarFront::saveValue, NULL);
	if(ret != 0)
	{

	}
	
	pthread_exit(NULL);
}

void CSonarFront::saveValue(void)
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
    	if ( micros()-timeoutstart>=SENSOR_TIMEOUT) return (-1.0);
    }
    startTimeUsec = micros();
    while ( digitalRead(mEcho) == HIGH )
    {
    	endTimeUsec = micros();
        if (endTimeUsec-timeoutstart>=SENSOR_TIMEOUT) return (-1.0);
    }

    travelTimeUsec = endTimeUsec - startTimeUsec;
    distanceCm = travelTimeUsec/58.0;

	//Save Sensor Data Class
	mData.insertData(1, (int)distanceCm);	
}

