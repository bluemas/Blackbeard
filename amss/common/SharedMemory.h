///////////////////////////////////////////////////////////
//  SharedMemory.h
//  Implementation of the Class SharedMemory
//  Created on:      31-10-2017 PM 7:55:17
//  Original author: bluem
///////////////////////////////////////////////////////////

#if !defined(EA_8783F2BF_3480_41e3_A466_4F4E71B15D13__INCLUDED_)
#define EA_8783F2BF_3480_41e3_A466_4F4E71B15D13__INCLUDED_

class SharedMemory
{

public:
	SharedMemory();
	virtual ~SharedMemory();

	void map();
	void unmap();

};
#endif // !defined(EA_8783F2BF_3480_41e3_A466_4F4E71B15D13__INCLUDED_)
