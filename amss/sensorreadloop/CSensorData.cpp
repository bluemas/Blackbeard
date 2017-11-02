// Sensor Data Class Source File

#include "CSensorData.h"
using namespace std;

CSensorData::CSensorData() {}
CSensorData::~CSensorData() {}
CSensorData* CSensorData::getInstance()
{
	if(mSensorData == NULL)
	{
		mSensorData = new CSensorData();
		return mSensorData;
	}
	else
	{
		return mSensorData;
	}
}

void CSensorData::insertData(int key, int value)
{
	if(mData[key] != mData.end())
	{
		mData.insert(pair<int, int>(key, value));
	}
	else
	{
		mData[key] = value;
	}
}

int CSensorData::getData(int key)
{
	int retVal = -1;

	if(mData[key] != mData.end())
		retVal = mData[key];
	
	return retVal;
}

int CSensorData::getDataCount(void)
{
	return mData.size();
}
