// Sensor Data Class Header File

#ifndef _CSENSORDATA_H
#define _CSENSORDATA_H

#include <map>

using namespace std

class CSensorData {
private:
	map<int, int> mData;
	CSensorData * mSensorData;
	CSensorData();
	
public:
	~CSensorData();
	static CSensorData* getInstance(void);

	void insertData(int key, int value);
	int getData(int key);
	int getDataCount(void);
}

#endif
