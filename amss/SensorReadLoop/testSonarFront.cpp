#include <iostream>
#include <wiringPi.h>
#include "CSonarFront.h"

int trigger = 28;
int echo = 29;

int main()
{
    if (wiringPiSetup() == -1) return -1;

	CSonarFront* sonarFront;
	sonarFront = sonarFront->getInstance();

	sonarFront->init(trigger, echo);
	
    while(1){
        cout << "Distance is " << sonarFront->getDistance(30000) << " cm." << endl;
    }
}
