///////////////////////////////////////////////////////////
//  SuspendMode.h
//  Implementation of the Class SuspendMode
//  Created on:      31-10-2017 PM 7:55:17
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_45A10C10_98C9_4af6_AA28_B08639D786CE__INCLUDED_)
#define EA_45A10C10_98C9_4af6_AA28_B08639D786CE__INCLUDED_

#include "ModeBase.h"
#include "../common/EventHandlerAdapter.h"

class SuspendMode : public ModeBase, public EventHandlerAdapter {
public:
	SuspendMode(MainController* mainController);
	~SuspendMode() {}

	void doEntryAction();

};
#endif // !defined(EA_45A10C10_98C9_4af6_AA28_B08639D786CE__INCLUDED_)
