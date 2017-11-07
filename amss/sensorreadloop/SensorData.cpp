// Sensor Data Class Source File

#include "SensorData.h"
#include <stdio.h>

using namespace std;

SensorData* SensorData::mSensorData = 0;

SensorData::SensorData() {}
SensorData::~SensorData() {}

SensorData* SensorData::getInstance()
{
	if(mSensorData == 0)
	{
		//Guard<Thread_Mutex> guard(singleton_lock_);
		//if(mSensorData == 0)
			mSensorData = new SensorData();
		//Destructor release lock automatically
	}
	return mSensorData;
}

void SensorData::insertData(int key, int value)
{
	map<int, int>::iterator it;
	
	it = mData.find(key);
	
	if(it == mData.end())
	{
		mData.insert(pair<int, int>(key, value));
	}
	else
	{
		mData[key] = value;
	}
}

int SensorData::getData(int key)
{
	int retVal = -1;
	map<int, int>::iterator it;
	
	it = mData.find(key);

	if(it != mData.end())
		retVal = mData[key];
	
	return retVal;
}

int SensorData::getDataCount(void)
{
	return mData.size();
}
