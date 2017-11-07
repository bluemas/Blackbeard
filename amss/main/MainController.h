///////////////////////////////////////////////////////////
//  MainController.h
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
#define EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_

#include "Initializer.h"
#include "CommandHandler.h"
#include "ModeManager.h"
#include "ModeBase.h"
#include "../common/Constant.h"
#include "../network/NetMessageEventAdapter.h"
#include "../network/NetworkManager.h"
#include "../servoencoder/CBehaviorExecutor.h"
#include "../sam/PathPlanner.h"
#include "../sam/WallRecognizer.h"
#include "AutonomousPathPlanningMode.h"
#include <map>

class MainController : public NetMessageEventAdapter
{

public:
	MainController();
	~MainController();

	void start();

    void setWallRecognizer(WallRecognizer* wallRecognizer);

private:
    void init();
    void runLoop();

    void eventHandler(EventBase* ev);

    void handleMessage(int type, void* data);

    ModeBase* mCurrentMode;
	std::map<RobotMode, ModeBase*> mModeList;
    AutonomousPathPlanningMode mAutoPathPlanning;

    Initializer* mInitializer;
    CommandHandler* mCCommandHandler;
    CBehaviorExecutor* mBehaviorExecutor;
    PathPlanner* mPathPlanner;
    ModeManager* mModeManager;
    WallRecognizer* mWallRecognizer;
};
#endif // !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
