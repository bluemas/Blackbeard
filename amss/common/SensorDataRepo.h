///////////////////////////////////////////////////////////
//  SensorDataRepo.h
//  Implementation of the Class SensorDataRepo
//  Created on:      31-10-2017 PM 7:55:16
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_DCDDC837_B7B9_432e_82A6_2E3467B20A63__INCLUDED_)
#define EA_DCDDC837_B7B9_432e_82A6_2E3467B20A63__INCLUDED_

#include "SharedMemory.h"

class SensorDataRepo : public SharedMemory
{

public:
	SensorDataRepo();
	virtual ~SensorDataRepo();

};
#endif // !defined(EA_DCDDC837_B7B9_432e_82A6_2E3467B20A63__INCLUDED_)