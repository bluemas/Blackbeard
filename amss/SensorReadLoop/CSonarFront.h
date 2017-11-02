// Sonar Sensor Class Header File

#ifndef _CSONARFRONT_H
#define _CSONARFRONT_H

#include <wiringPi.h>
#include <pthread.h>
#include "CSensorReaderLoop.h"
#include "CSensorData.h"

#define PIN_NUM_TRIGGER		28
#define PIN_NUM_ECHO		29
#define	SENSOR_TIMEOUT		30000

class CSonarFront:public CSensorReaderLoop {
private:
	int mEcho;
	int mTrigger;
	static CSonarFront * mSonar;
	pthread_t mThread;
	CSensorData * mData;
	CSonarFront();
	
public:
	~CSonarFront();
	static CSonarFront* getInstance(void);

	void init(void);
	void start(void);
	void saveValue(void);
}

#endif
