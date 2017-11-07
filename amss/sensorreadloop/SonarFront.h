// Sonar Sensor Class Header File

#ifndef _SONARFRONT_H
#define _SONARFRONT_H

#include <wiringPi.h>
#include <pthread.h>
#include <stdio.h>
#include "SensorReaderLoop.h"
#include "SensorData.h"

#define PIN_NUM_TRIGGER		28
#define PIN_NUM_ECHO		29
#define	SENSOR_TIMEOUT		30000

class SonarFront:public SensorReaderLoop {
private:
	int mEcho;
	int mTrigger;
	SensorData * mData;
	
public:
	SonarFront();
	virtual void run();
};

#endif
