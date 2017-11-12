#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include "BehaviorExecutor.h"
#include "../common/Constants.h"

int main()
{
	BehaviorExecutor be;

	be.setCamDefault();

	//be.manualMove(Direction::forward);
	//usleep(700000);
	//be.stop();
	//sleep(1);
	//be.manualMove(Direction::left);

	be.move(Direction::left);
	sleep(1);
	be.move(Direction::right);
	sleep(1);
	be.move(Direction::backward);
/*
	be.searchSign(Direction::left);
	sleep(20);
	be.searchSign(Direction::forward);
	sleep(20);
	be.searchSign(Direction::right);
	sleep(20);

	be.panAndTilt(CamDirection::panleft);
	sleep(5);
	be.stopPanAndTilt();
	
	be.panAndTilt(CamDirection::panright);
	sleep(5);
	be.stopPanAndTilt();
	
	be.panAndTilt(CamDirection::tiltup);
	sleep(5);
	be.stopPanAndTilt();
	
	be.panAndTilt(CamDirection::tiltdown);
	sleep(5);
	be.stopPanAndTilt();
*/
}
