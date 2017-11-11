///////////////////////////////////////////////////////////
//  ModeBase.h
//  Implementation of the Class ModeBase
//  Created on:      31-10-2017 PM 7:55:16
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_244B529B_9638_4b0a_AE45_9D4E1717848B__INCLUDED_)
#define EA_244B529B_9638_4b0a_AE45_9D4E1717848B__INCLUDED_

#include "../common/Constants.h"
#include "../common/event/EventHandlerAdapter.h"

class MainController;

class ModeBase : public EventHandlerAdapter {

public:
	ModeBase();
	virtual ~ModeBase();

	RobotMode getModeName();

    virtual void doEntryAction() {};
    virtual void doExitAction() {};

protected:
	RobotMode mModeName;
	MainController* mMainController;

};
#endif // !defined(EA_244B529B_9638_4b0a_AE45_9D4E1717848B__INCLUDED_)
