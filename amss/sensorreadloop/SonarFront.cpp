// Sonar Sensor Class Source File

#include "SonarFront.h"

SonarFront::SonarFront()
{
    mTrigger = PIN_NUM_TRIGGER;
    mEcho = PIN_NUM_ECHO;
    pinMode(mTrigger, OUTPUT);
    pinMode(mEcho, INPUT);
    digitalWrite(mTrigger, LOW);
    delay(500);
}

void SonarFront::read(void)
{
    long startTimeUsec,endTimeUsec = 0,travelTimeUsec,timeoutstart;
    double distanceMm;

    if ((mTrigger==-1) || (mEcho==-1)) return;

    delay(10);
    digitalWrite(mTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(mTrigger, LOW);

    timeoutstart=micros();

    while (digitalRead(mEcho) == LOW)
    {
        if ( micros()-timeoutstart>=SENSOR_TIMEOUT)
        {
            //printf("return 1st\n");
            continue;
        }
    }
    startTimeUsec = micros();
    while ( digitalRead(mEcho) == HIGH )
    {
        endTimeUsec = micros();
        if (endTimeUsec-timeoutstart>=SENSOR_TIMEOUT)
        {
            //printf("return 2nd\n");
            continue;
        }
    }

    travelTimeUsec = endTimeUsec - startTimeUsec;
    distanceMm = travelTimeUsec/5.8;

    //Save Sensor Data Class
    inputData(SensorType::front, (int)distanceMm);
}

