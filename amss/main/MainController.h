///////////////////////////////////////////////////////////
//  MainController.h
//  Implementation of the Class MainController
//  Created on:      31-10-2017 PM 7:55:15
//  Original author: bluemas
///////////////////////////////////////////////////////////

#if !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
#define EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_

#include "ModeBase.h"
#include "AutonomousPathPlanningMode.h"
#include "ManualMode.h"
#include "../camera/DotRecognizer.h"
#include "../camera/ImageRecognizer.h"
#include "../camera/LineRecognizer.h"
#include "../camera/SignRecognizer.h"
#include "../common/Constants.h"
#include "../common/event/EventHandlerAdapter.h"
#include "../network/NetworkManager.h"
#include "../servoencoder/BehaviorExecutor.h"
#include "../sam/PathPlanner.h"
#include "../sam/WallRecognizer.h"
#include "../camera/ImageRecognizer.h"
#include <map>

class MainController :
    public WallSensingEventHandler,
    public WallCollisionEventHandler,
    public SquareRecognizedEventHandler,
    public SignRecognizedEventHandler,
    public RedDotRecognizedEventHandler,
    public LineRecognizedEventHandler,
    public NetMessageEventAdapter {

public:
    MainController();
    ~MainController();

    void start();
    void setImageRecognizer(ImageRecognizer* imageRecognizer);
    void setNetworkManager(NetworkManager* networkManger);
    void setPathPlanner(PathPlanner* pathPlanner);

    BehaviorExecutor* behaviorExecutor();
    ImageRecognizer* imageRecognizer();
    PathPlanner* pathPlanner();
    NetworkManager* networkManager();

    void setCurrentMode(RobotMode mode);
    ModeBase* currentMode();

private:
    void init();
    void createModeInstances();
    void runLoop();

    void handleWallSensingEvent(const WallSensingEvent ev);
    void handleWallCollisionEvent(const WallCollisionEvent ev);
    void handleSquareRecognizedEvent(const SquareRecognizedEvent ev);
    void handleSignRecognizedEvent(const SignRecognizedEvent ev);
    void handleRedDotRecognizedEvent(const RedDotRecognizedEvent ev);

    void handleLineRecognizedEvent(const LineRecognizedEvent ev);

    void handleMessage(int type, void* data);
    void initializeRobot();

    void moveRobot(const void *data);
    std::map<RobotMode, ModeBase*> mModeList;
    ModeBase* mCurrentMode;
    BehaviorExecutor mBehaviorExecutor;
    PathPlanner* mPathPlanner;
    NetworkManager* mNetworkManager;
    SignRecognizer* mSignRecognizer;

    ImageRecognizer* mImageRecognizer;
};
#endif // !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
