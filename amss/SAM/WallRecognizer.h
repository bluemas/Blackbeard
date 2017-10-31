///////////////////////////////////////////////////////////
//  WallRecognizer.h
//  Implementation of the Class WallRecognizer
//  Created on:      31-10-2017 PM 7:55:18
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_2D6F161F_28A2_4fe7_BD92_A210327AF5D3__INCLUDED_)
#define EA_2D6F161F_28A2_4fe7_BD92_A210327AF5D3__INCLUDED_

#include "MazeMapper.h"

class WallRecognizer
{

public:
	WallRecognizer();
	virtual ~WallRecognizer();
	MazeMapper *m_MazeMapper;

};
#endif // !defined(EA_2D6F161F_28A2_4fe7_BD92_A210327AF5D3__INCLUDED_)
