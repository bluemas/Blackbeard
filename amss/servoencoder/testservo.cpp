#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "BehaviorExecutor.h"
#include "../common/Constants.h"

int main()
{
	BehaviorExecutor be;

	be.setCamDefaultTrackLine();

	//be.manualMove(Direction::forward);
	//usleep(1700000);
	//be.stop();
	//sleep(1);
	//be.manualMove(Direction::left);
	be.searchSign(Direction::left);
	sleep(10);
	be.searchSign(Direction::right);
	sleep(10);
	be.searchSign(Direction::forward);
	sleep(10);

}
