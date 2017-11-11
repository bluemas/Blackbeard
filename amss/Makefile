CXXFLAGS=-O2 -g -Wall -std=gnu++11 -lpthread -lwiringPi -lvl53l0x

OBJS = common/event/EventHandlerAdapter.o common/event/EventBase.o \
       common/event/WallCollisionEvent.o common/event/WallSensingEvent.o \
       common/event/LineRecognizedEvent.o common/event/RedDotRecognizedEvent.o \
       common/event/SignRecognizedEvent.o common/event/SquareRecognizedEvent.o \
       common/event/LineRecognizedEventHandler.o common/event/RedDotRecognizedEventHandler.o \
       common/event/SignRecognizedEventHandler.o common/event/SquareRecognizedEventHandler.o \
       sam/WallRecognizer.o sam/MapRepo.o sam/MazeMapper.o sam/PathPlanner.o \
       sensorreadloop/SensorReader.o sensorreadloop/SonarFront.o \
       sensorreadloop/FlightSensorLeft.o sensorreadloop/FlightSensorRight.o \
       sensorreadloop/SensorData.o \
       test/MainController.o main.o

LIBS = -Lsensorreadloop

TARGET = AMSS

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

clean:
	rm -rf $(OBJS) $(TARGET) 
