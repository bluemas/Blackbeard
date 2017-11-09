///////////////////////////////////////////////////////////
//  AutonomousPathPlanningMode.h
//  Implementation of the Class AutonomousPathPlanningMode
//  Created on:      31-10-2017 PM 7:55:13
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_4F2E3F85_F445_4e38_AAF9_70029F74B0D1__INCLUDED_)
#define EA_4F2E3F85_F445_4e38_AAF9_70029F74B0D1__INCLUDED_

#include "ModeBase.h"
#include "../common/EventHandlerAdapter.h"

class AutonomousPathPlanningMode : public ModeBase, public EventHandlerAdapter {
public:
	AutonomousPathPlanningMode(MainController* mainController);
	~AutonomousPathPlanningMode();

    void doEntryAction();

private:

};
#endif // !defined(EA_4F2E3F85_F445_4e38_AAF9_70029F74B0D1__INCLUDED_)
