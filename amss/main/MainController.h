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
#include "NetworkManager.h"
#include "BehaviorExecutor.h"
#include "PathPlanner.h"
#include "DotRecognizer.h"
#include "ImageSender.h"
#include "LineRecognizer.h"
#include "SignRecognizer.h"
#include "WallRecognizer.h"
#include "ModeManager.h"

class MainController
{

public:
	MainController();
	virtual ~MainController();
	Initializer *m_Initializer;
	CCommandHandler *m_CCommandHandler;
	NetworkManager *m_NetworkManager;
	BehaviorExecutor *m_BehaviorExecutor;
	PathPlanner *m_PathPlanner;
	DotRecognizer *m_DotRecognizer;
	ImageSender *m_ImageSender;
	LineRecognizer *m_LineRecognizer;
	SignRecognizer *m_SignRecognizer;
	WallRecognizer *m_WallRecognizer;
	ModeManager *m_ModeManager;

	void init();
	void runLoop();
	static void start();

};
#endif // !defined(EA_6F5C1742_CB6A_41e4_8863_8CDFEDFB70C0__INCLUDED_)
