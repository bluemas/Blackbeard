// Sensor Reading Loop Class Header File

#ifndef _CSENSORREADER_H
#define _CSENSORREADER_H

class CSensorReader {
private:
	// need to figure out how to add other sensors...
	int distanceFront;
	int distanceLeft;
	int distanceRight;
	static CSensorReader mSensorReader;

	CSensorReader();
	
public:
	~CSensorReader();

	static CSensorReader * getInstance();
	void startReadingSensor(void);
	void saveSensorValue(void);	
}

#endif
