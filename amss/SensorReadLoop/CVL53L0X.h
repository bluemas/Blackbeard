//VL53L0X Flight Range Sensor Class Header File

#ifndef _CVL53L0X_H
#define _CVL53L0X_H

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

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

class CVL53L0X {
private:
	VL53L0X_Dev_t mMyDevice;
	VL53L0X_Dev_t * mpMyDevice = &mDevice;
	VL53L0X_RangingMeasurementData_t mRangingMeasurementData;
	VL53L0X_RangingMeasurementData_t * mpRangingMeasurementData;
	
	void print_pal_error(VL53L0X_Error Status);
	VL53L0X_Error WaitMeasurementDataReady(VL53L0X_DEV Dev);
	VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev);
	
public:
	CVL53L0X();
	~CVL53L0X();
	
	void startRanging(int mode, uint8_t i2c_address, uint8_t TCA9548A_Device, uint8_t TCA9548A_Address);
	int32_t getDistance(void);
	void stopRanging(void);	
}

#endif
