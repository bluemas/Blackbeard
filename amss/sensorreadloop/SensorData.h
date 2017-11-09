// Sensor Data Class Header File

#ifndef _CSENSORDATA_H
#define _CSENSORDATA_H

#include <map>
#include "../common/Constants.h"

using namespace std;

class SensorData {
private:
	map<SensorType, int> mData;
	
	static SensorData* mSensorData;
	SensorData();
	
public:
	~SensorData();
	static SensorData* getInstance();

	void insertData(SensorType key, int value);
	int getData(SensorType key);
	int getDataCount(void);
};

#endif
