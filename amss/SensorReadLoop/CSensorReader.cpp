// Sensor Reading Loop Class Source File

#include "CSensorReader.h"

CSensorReader::CSensorReader() {}
CSensorReader::~CSensorReader();
CSensorReader * CSensorReader::getInstance()
{
	if(mSensorReader == NULL)
	{
		mSensorReader = new CSensorReader();
	}
	else
	{
		return mSensorReader;
	}
}

void CSensorReader::startReadingSensor(void)
{

}

void CSensorReader::saveSensorValue(void)
{

}
