// Sensor Reading Loop Class Header File

#ifndef _SENSORREADER_H
#define _SENSORREADER_H

#include <stdio.h>
#include "SensorData.h"
#include "../common/Constants.h"

class SensorReader {
private:
    SensorData* mData;

public:
    SensorReader();
    virtual ~SensorReader();
    virtual void read() =0;
    void putData(SensorType type, int value);
};

#endif
