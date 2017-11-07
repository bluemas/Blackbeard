#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "CSonarFront.h"
#include "CFlightSensorLeft.h"
#include "CFlightSensorRight.h"
#include "CSensorData.h"


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
	sonar.start();
	
	FlightSensorLeft sleft;
	sleft.start();
	
	FlightSensorRight sright;
	sright.start();

	SonarFront sonar2;
}
