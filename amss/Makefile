CXXFLAGS=-O2 -g -Wall -std=gnu++11 -lpthread -lwiringPi -lvl53l0x -lraspicamcv -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_video -I/usr/local/include -I/home/pi/git/robidouille/raspicam_cv

OBJS = \
	common/RecognizerBase.o common/event/EventHandlerAdapter.o common/event/EventBase.o \
	common/event/WallCollisionEvent.o common/event/WallSensingEvent.o \
	common/event/LineRecognizedEvent.o common/event/RedDotRecognizedEvent.o \
	common/event/SignRecognizedEvent.o common/event/SquareRecognizedEvent.o \
	common/event/WallCollisionEventHandler.o common/event/WallSensingEventHandler.o \
	common/event/LineRecognizedEventHandler.o common/event/RedDotRecognizedEventHandler.o \
	common/event/SignRecognizedEventHandler.o common/event/SquareRecognizedEventHandler.o \
	sam/WallRecognizer.o sam/MapData.o sam/MazeMapper.o sam/PathPlanner.o sam/MazeGrid.o \
	camera/CameraReader.o camera/ImageRecognizer.o camera/DotRecognizer.o \
	camera/SquareRecognizer.o camera/LineRecognizer.o camera/SignRecognizer.o \
	camera/ImageSender.o camera/ImageData.o \
	sensorreadloop/SensorReader.o sensorreadloop/SonarFront.o \
	sensorreadloop/FlightSensorLeft.o sensorreadloop/FlightSensorRight.o \
	sensorreadloop/SensorData.o \
	servoencoder/BehaviorExecutor.o servoencoder/PID.o servoencoder/ServoEncoder.o \
	network/TCPSocket.o network/UDPSocket.o \
	network/NetworkManager.o \
	main/ModeBase.o main/AutonomousMovingMode.o main/AutonomousPathPlanningMode.o \
	main/AutonomousSignRecognitionMode.o main/ManualMode.o main/SuspendMode.o \
	main/MainController.o \
	main.o

LIBS = -Lsensorreadloop -L/home/pi/git/robidouille/raspicam_cv -L/usr/local/lib

TARGET = AMSS

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

clean:
	rm -rf $(OBJS) $(TARGET)
