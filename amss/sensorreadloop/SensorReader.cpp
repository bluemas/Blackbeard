// Sensor Reading Loop Class Source File

#include "SensorReader.h"

SensorReader::SensorReader()
{
	mData = SensorData::getInstance();
}

SensorReader::~SensorReader() {}

void SensorReader::inputData(SensorType type, int value)
{
	mData->putData(type, value);
}

