#include <iostream>
#include "CSonarFront.h"

using namespace std;

int main()
{
	CSonarFront* test = CSonarFront::getInstance();
	CSensorData* data = CSensorData::getInstance();

	test->init();
	test->start();
	
}
