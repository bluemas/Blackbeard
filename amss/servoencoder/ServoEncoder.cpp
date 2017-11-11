// ServoEncoder Class Source File

#include "ServoEncoder.h"

ServoEncoder* ServoEncoder::mpServo = 0;

ServoEncoder::ServoEncoder(){
    mServoFd = -1;
}

ServoEncoder::~ServoEncoder(){

}

ServoEncoder* ServoEncoder::getInstance()
{
    if(mpServo == NULL)
    {
        mpServo = new ServoEncoder();
        return mpServo;
    }
    else
    {
        return mpServo;
    }
}

int ServoEncoder::openServos(void)
{
    if(mServoFd != -1)
    {
        return (0);
    }

    mServoFd = open("/dev/servoblaster", O_RDWR);

    if(mServoFd < 0)
    {
        return (-1);
    }

    sleep(1);	//wait for the servo driver to stablize
    return (0);
}

void ServoEncoder::closeServos(void)
{
    if(mServoFd == -1)
    {
        return;
    }

    close(mServoFd);
    mServoFd = -1;
}

void ServoEncoder::resetServos(void)
{
    int value = SERVO_CENTER_OR_STOP;

    setServoPosition(CAMERA_PAN, value);
    setServoPosition(CAMERA_TILT, value);
    setServoPosition(RIGHT_WHEEL, value);
    setServoPosition(LEFT_WHEEL, value);
}

int ServoEncoder::getServoMinVal(unsigned int servo)
{
    int retVal = 0;
    switch(servo){
    case CAMERA_PAN:
        retVal = PAN_CAMERA_MIN;
        break;
    case CAMERA_TILT:
        retVal = TILT_CAMERA_MIN;
        break;
    case RIGHT_WHEEL:
    case LEFT_WHEEL:
        retVal = WHEEL_MIN;
        break;
    }
    return retVal;
}

int ServoEncoder::getServoMaxVal(unsigned int servo)
{
    int retVal = 0;
    switch(servo){
    case CAMERA_PAN:
        retVal = PAN_CAMERA_MAX;
        break;
    case CAMERA_TILT:
        retVal = TILT_CAMERA_MAX;
        break;
    case RIGHT_WHEEL:
    case LEFT_WHEEL:
        retVal = WHEEL_MAX;
        break;
    }
    return retVal;
}

void ServoEncoder::setServoVal(unsigned int servo, int position)
{
    switch(servo){
    case CAMERA_PAN:
        mPan = position;
        break;
    case CAMERA_TILT:
        mTilt = position;
        break;
    case RIGHT_WHEEL:
        mWheelRSpeed = position;
        break;
    case LEFT_WHEEL:
        mWheelLSpeed = position;
        break;
    }
}

int ServoEncoder::setServoPosition(unsigned int servo,int position)
{
    char buf[256];
    ssize_t len;
    int setPos = 0;
    int minPos = 0;
    int maxPos = 0;

    if(mServoFd == -1) return(-1);

    if(servo >= NUM_SERVOS) return(-1);

    setPos = position;
    minPos = getServoMinVal(servo);
    maxPos = getServoMaxVal(servo);

    if(setPos > maxPos) setPos = maxPos;
    else if(setPos < minPos) setPos = minPos;
    else {}

    setServoVal(servo,setPos);

    sprintf(buf,"%d=%d\n", servo, setPos);
    len=strlen(buf);
    if (write(mServoFd, buf, len) != len) return(-1);
    fsync(mServoFd);
    return(0);
}

void ServoEncoder::setWheelSpeed(int left,int right)
{
    left = left + SERVO_CENTER_OR_STOP;
    right = -right + SERVO_CENTER_OR_STOP;

    printf("%d, %d\n", left, right);
    setServoPosition(LEFT_WHEEL, left);
    setServoPosition(RIGHT_WHEEL, right);
}

void ServoEncoder::setCameraServosLineTrackMode(int pan,int tilt)
{
    pan = TRK_LINE_CAM_PAN;
    tilt = TRK_LINE_CAM_TILT;
    setServoPosition(CAMERA_PAN, pan);
    setServoPosition(CAMERA_TILT, tilt);
}

void ServoEncoder::setCameraServosLineTrackMode(void)
{
    int pan = TRK_LINE_CAM_PAN;
    int tilt = TRK_LINE_CAM_TILT;
    setServoPosition(CAMERA_PAN, pan);
    setServoPosition(CAMERA_TILT, tilt);
}

