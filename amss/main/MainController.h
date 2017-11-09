///////////////////////////////////////////////////////////
//  MainController.h
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
#define EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_

#include "Initializer.h"
#include "ModeBase.h"
#include "AutonomousPathPlanningMode.h"
#include "../common/Constants.h"
#include "../network/NetworkManager.h"
#include "../servoencoder/BehaviorExecutor.h"
#include "../sam/PathPlanner.h"
#include "../sam/WallRecognizer.h"
#include "../camera/LineRecognizer.h"
#include "../camera/SignRecognizer.h"
#include "../camera/DotRecognizer.h"
#include "../common/event/EventHandlerAdapter.h"
#include "ManualMode.h"
#include <map>

class MainController : public EventHandlerAdapter, public NetMessageEventAdapter {

public:
    MainController();
    ~MainController();

    void start();
    void setWallRecognizer(WallRecognizer* wallRecognizer);
    void setLineRecognizer(LineRecognizer* lineRecognizer);
    void setDotRecognizer(DotRecognizer* dotRecognizer);
    void setSignRecognizer(SignRecognizer* signRecognizer);
    void setNetworkManager(NetworkManager* networkManger);

    PathPlanner* pathPlanner();
    BehaviorExecutor* behaviorExecutor();
    NetworkManager* networkManager();

    void setCurrentMode(RobotMode mode);
    ModeBase* currentMode();

private:
    void init();
    void runLoop();

    void handleWallCollisionEvent(const handleCollisionEvent ev);
    void handleLineRecognizedEvent(const LineRecognizedEvent ev);
    void handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev);
    void handleSignRecognizedEvent(const SignRecognizedEvent ev);
    void handleSquareRecognizedEvent(const SquareRecognizedEvent ev);

    void handleMessage(int type, void* data);

    void initializeRobot();
    void moveRobot(const void *data);

    std::map<RobotMode, ModeBase*> mModeList;
    ModeBase* mCurrentMode;
    Initializer mInitializer;
    BehaviorExecutor mBehaviorExecutor;
    PathPlanner mPathPlanner;
    NetworkManager* mNetworkManager;
    SignRecognizer* mSignRecognizer;
};
#endif // !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
