///////////////////////////////////////////////////////////
//  MainController.h
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
#define EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_

#include "Initializer.h"
#include "CCommandHandler.h"
#include "ModeManager.h"
#include "ModeBase.h"
#include "..\network\IMessageListener.h"
#include "..\network\NetworkManager.h"
#include "..\servoencoder\CBehaviorExecutor.h"
#include "..\sam\PathPlanner.h"

class MainController : public IMessageListener
{

public:
	MainController();
	~MainController();

	static void start();
    void handleMessage(int type, void* payload);

private:
    void init();
    void runLoop();

    ModeBase* mCurrentMode;

    Initializer *m_Initializer;
    CCommandHandler *m_CCommandHandler;
    CBehaviorExecutor *m_BehaviorExecutor;
    PathPlanner *m_PathPlanner;
    ModeManager *m_ModeManager;
};
#endif // !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
