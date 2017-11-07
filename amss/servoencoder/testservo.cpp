#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "BehaviorExecutor.h"

int main()
{
	BehaviorExecutor be;

	be.setCamDefaultTrackLine();

	be.manualMove(forward);
	sleep(2);
	be.stop();	
}
