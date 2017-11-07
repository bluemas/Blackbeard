// CServoEncoder Class Header File

#ifndef SERVOENCORDER_H
#define SERVOENCORDER_H

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define SERVO_CENTER_OR_STOP	150

#define TRK_LINE_CAM_PAN		149	//157
#define TRK_LINE_CAM_TILT		211	//192

#define CAMERA_PAN				0
#define CAMERA_TILT				1		
#define RIGHT_WHEEL				2
#define LEFT_WHEEL				3
#define NUM_SERVOS				4

#define PAN_CAMERA_MIN			50
#define PAN_CAMERA_MAX			250
#define TILT_CAMERA_MIN			80
#define TILT_CAMERA_MAX			220 
#define WHEEL_MAX				200
#define WHEEL_MIN				100

class ServoEncoder
{
private:
	int	mServoFd;
	int mPan;
	int mTilt;
	int mWheelLSpeed;
	int mWheelRSpeed;
	static ServoEncoder * mpServo;
	ServoEncoder();
	int	getServoMinVal(unsigned int servo);
	int	getServoMaxVal(unsigned int servo);
	void setServoVal(unsigned int servo, int position);
	
public:
	~ServoEncoder();
	static ServoEncoder* getInstance();

	int openServos(void);
	void closeServos(void);
	void resetServos(void);
	int  setServoPosition(unsigned int servo,int position);
	void setWheelSpeed(int left,int right);
	void setCameraServosLineTrackMode(int pan,int tilt);
	void setCameraServosLineTrackMode(void);
};
#endif // CSERVOENCODER_H
