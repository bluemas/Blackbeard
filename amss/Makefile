CXXFLAGS=-O2 -g -Wall -std=gnu++11 -lpthread -lwiringPi -lvl53l0x

OBJS = common/RecognizerBase.o common/event/EventHandlerAdapter.o common/event/EventBase.o \
	common/event/WallCollisionEvent.o common/event/WallSensingEvent.o \
	common/event/LineRecognizedEvent.o common/event/RedDotRecognizedEvent.o \
	common/event/SignRecognizedEvent.o common/event/SquareRecognizedEvent.o \
	common/event/WallCollisionEventHandler.o common/event/WallSensingEventHandler.o \
	common/event/LineRecognizedEventHandler.o common/event/RedDotRecognizedEventHandler.o \
	common/event/SignRecognizedEventHandler.o common/event/SquareRecognizedEventHandler.o \
	sam/WallRecognizer.o sam/MapData.o sam/MazeMapper.o sam/PathPlanner.o \
	camera/CameraReader.o camera/ImageRecognizer.o camera/DotRecognizer.o \
	camera/SquareRecognizer.o camera/LineRecognizer.o camera/SignRecognizer.o \
	camera/ImageSender.o \
	sensorreadloop/SensorReader.o sensorreadloop/SonarFront.o \
	sensorreadloop/FlightSensorLeft.o sensorreadloop/FlightSensorRight.o \
	sensorreadloop/SensorData.o \
	servoencoder/BehaviorExecutor.o servoencoder/PID.o servoencoder/ServoEncoder.o \
	network/TCPSocket.o network/UDPSocket.o \
	network/NetworkManager.o \
	main/AutonomousMovingMode.o main/AutonomousPlannerMode.o \
	main/AutonomousSignRecognitionMode.o ManualMode.o main/SuspendMode.o \
	main/ModeBase.o main/MainController.o \
	main.o

LIBS = -Lsensorreadloop

TARGET = AMSS

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

clean:
	rm -rf $(OBJS) $(TARGET)
