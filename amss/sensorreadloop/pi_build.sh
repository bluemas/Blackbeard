#!/bin/bash
g++ test.cpp -o test -std=c++11 -lwiringPi -lpthread -lvl53l0x SensorReader.cpp SonarFront.cpp SensorData.cpp FlightSensorLeft.cpp FlightSensorRight.cpp
