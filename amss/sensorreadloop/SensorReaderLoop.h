// Sensor Reading Loop Class Header File

#ifndef _SENSORREADERLOOP_H
#define _SENSORREADERLOOP_H

#include <pthread.h>
#include <stdio.h>

class SensorReaderLoop {
protected:
	pthread_t mThread;
	bool mRunFlag;
public:
	SensorReaderLoop();
	virtual ~SensorReaderLoop();
	virtual void run() = 0;
	static void* run_(void *);
	void start();
	void stop();
	bool isRun();	
};

#endif
