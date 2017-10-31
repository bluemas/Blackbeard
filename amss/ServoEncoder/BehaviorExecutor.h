///////////////////////////////////////////////////////////
//  BehaviorExecutor.h
//  Implementation of the Class BehaviorExecutor
//  Created on:      31-10-2017 PM 7:55:14
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_1ABEB96D_B497_4b55_958A_E4E9216DD679__INCLUDED_)
#define EA_1ABEB96D_B497_4b55_958A_E4E9216DD679__INCLUDED_

#include "ServoEncoder.h"

class BehaviorExecutor
{

public:
	BehaviorExecutor();
	virtual ~BehaviorExecutor();
	ServoEncoder *m_ServoEncoder;

};
#endif // !defined(EA_1ABEB96D_B497_4b55_958A_E4E9216DD679__INCLUDED_)
