// Sensor Reading Loop Class Source File

#include "SensorReaderLoop.h"

SensorReaderLoop::SensorReaderLoop()
{
	this->mRunFlag = false;
}

SensorReaderLoop::~SensorReaderLoop()
{
	if(this->isRun())
	{
		this->stop();
	}
}

bool SensorReaderLoop::isRun()
{
	return this->mRunFlag;
}

void* SensorReaderLoop::run_(void* aThis)
{	
	SensorReaderLoop* pThis = (SensorReaderLoop*)aThis;
	//while(pThis->isRun())
	{
		pThis->run();
	}

	return 0;
}

void SensorReaderLoop::start()
{
	this->mRunFlag = true;
	pthread_create(&mThread, NULL, &SensorReaderLoop::run_, (void*)this);
}

void SensorReaderLoop::stop()
{
	this->mRunFlag = false;
	pthread_join(mThread, NULL);
}
