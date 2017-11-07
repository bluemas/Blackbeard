//VL53L0X Flight Range Sensor Class Header File

#ifndef _CFLIGHTSENSORRIGHT_H
#define _CFLIGHTSENSORRIGHT_H

#include "VL53L0X_API/vl53l0x_api.h"
#include "VL53L0X_API/vl53l0x_platform.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include "SensorReaderLoop.h"
#include "SensorData.h"

#define VERSION_REQUIRED_MAJOR 1
#define VERSION_REQUIRED_MINOR 0
#define VERSION_REQUIRED_BUILD 2

#define VL53L0X_DEFAULT_ADDRESS 0x29

#define VL53L0X_GOOD_ACCURACY_MODE      0   // Good Accuracy mode
#define VL53L0X_BETTER_ACCURACY_MODE    1   // Better Accuracy mode
#define VL53L0X_BEST_ACCURACY_MODE      2   // Best Accuracy mode
#define VL53L0X_LONG_RANGE_MODE         3   // Longe Range mode
#define VL53L0X_HIGH_SPEED_MODE         4   // High Speed mode

#define MAX_DEVICES                     16

class FlightSensorRight:public SensorReaderLoop {
private:
	VL53L0X_Dev_t mMyDevice;
	VL53L0X_Dev_t* mpMyDevice;
	VL53L0X_RangingMeasurementData_t mRangingMeasurementData;
	VL53L0X_RangingMeasurementData_t* mpRangingMeasurementData;
	SensorData * mData;
	uint32_t mTiming;
	
	void print_pal_error(VL53L0X_Error Status);
	VL53L0X_Error WaitMeasurementDataReady(VL53L0X_DEV Dev);
	VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev);	
	void startRanging(int mode, uint8_t i2c_address, uint8_t TCA9548A_Device, uint8_t TCA9548A_Address);
	int32_t getDistance(void);
	uint32_t GetTiming(void); 
	
public:
	FlightSensorRight();

	virtual void run();
	void stopRanging(void);	
};

#endif
