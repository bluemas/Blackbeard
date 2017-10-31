///////////////////////////////////////////////////////////
//  SensorReader.h
//  Implementation of the Class SensorReader
//  Created on:      31-10-2017 PM 7:55:16
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_397F8FF4_9EB8_4190_B041_99B817D6B948__INCLUDED_)
#define EA_397F8FF4_9EB8_4190_B041_99B817D6B948__INCLUDED_

#include "Thread.h"

class SensorReader : public Thread
{

public:
	SensorReader();
	virtual ~SensorReader();

};
#endif // !defined(EA_397F8FF4_9EB8_4190_B041_99B817D6B948__INCLUDED_)
