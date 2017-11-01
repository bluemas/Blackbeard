// Sonar Sensor Class Header File

#ifndef _CSONARFRONT_H
#define _CSONARFRONT_H

#include <wiringPi.h>

class CSonarFront{
private:
	int mEcho;
	int mTrigger;
	static CSonarFront * mSonar;
	CSonarFront();
	
public:
	~CSonarFront();
	static CSonarFront* getInstance(void);
	void init(int _trigger, int _echo);
	double getDistance(int timeout);
}

#endif
