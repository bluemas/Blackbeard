#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "SonarFront.h"
#include "FlightSensorLeft.h"
#include "FlightSensorRight.h"
#include "SensorData.h"


int main()
{
    if (wiringPiSetup() == -1) return -1;
	
	if(VL53L0X_i2c_init("/dev/i2c-1")==-1)
	{
		 printf("VL53L0X_i2c_init failed\n");
		 exit(0);
	}

	SensorData* data = SensorData::getInstance();
	
	SonarFront sonar;
	sonar.read();
		
	FlightSensorLeft sleft;
	sleft.read();
	
	FlightSensorRight sright;
	sright.read();

	printf("Data size = %d\n", data->getDataCount());
	printf("Data - Front : %d, Left : %d, Right : %d\n", data->getData(SensorType::front), data->getData(SensorType::left), data->getData(SensorType::right));
}
