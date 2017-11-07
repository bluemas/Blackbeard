#!/bin/bash
g++ test.cpp -o test -lwiringPi -lpthread -lvl53l0x SensorReaderLoop.cpp SonarFront.cpp SensorData.cpp FlightSensorLeft.cpp FlightSensorRight.cpp
