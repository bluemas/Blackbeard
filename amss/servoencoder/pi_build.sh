#!/bin/bash
g++ testservo.cpp -o testservo -std=c++11 -lpthread BehaviorExecutor.cpp PID.cpp ServoEncoder.cpp
