// Sensor Reading Loop Class Header File

#ifndef _CSENSORREADERLOOP_H
#define _CSENSORREADERLOOP_H

class CSensorReaderLoop {
public:
	virtual void init(void) = 0;
	virtual void start(void) = 0;
	virtual void saveValue(void) = 0;
}

#endif
