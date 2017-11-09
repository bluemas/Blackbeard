// Sonar Sensor Class Header File

#ifndef _SONARFRONT_H
#define _SONARFRONT_H

#include <wiringPi.h>
#include <stdio.h>
#include "SensorReader.h"
#include "../common/Constants.h"

#define PIN_NUM_TRIGGER		28
#define PIN_NUM_ECHO		29
#define	SENSOR_TIMEOUT		30000

class SonarFront:public SensorReader {
private:
	int mEcho;
	int mTrigger;
	
public:
	SonarFront();
	virtual void read();
};

#endif
