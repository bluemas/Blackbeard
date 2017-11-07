// Sensor Data Class Header File

#ifndef _CSENSORDATA_H
#define _CSENSORDATA_H

#include <map>

using namespace std;

class SensorData {
private:
	map<int, int> mData;
	
	static SensorData* mSensorData;
	SensorData();
	
public:
	~SensorData();
	static SensorData* getInstance();

	void insertData(int key, int value);
	int getData(int key);
	int getDataCount(void);
};

#endif
