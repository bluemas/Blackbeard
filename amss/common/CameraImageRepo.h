///////////////////////////////////////////////////////////
//  CameraImageRepo.h
//  Implementation of the Class CameraImageRepo
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_7E37756C_D328_4988_9BEF_5432F9957535__INCLUDED_)
#define EA_7E37756C_D328_4988_9BEF_5432F9957535__INCLUDED_

#include "SharedMemory.h"

class CameraImageRepo : public SharedMemory
{

public:
	CameraImageRepo();
	virtual ~CameraImageRepo();

};
#endif // !defined(EA_7E37756C_D328_4988_9BEF_5432F9957535__INCLUDED_)
