CXXFLAGS=-O2 -g -Wall -std=gnu++11 -lpthread -lwiringPi -lvl53l0x -Lsensorreadloop

OBJS = common/event/EventHandlerAdapter.o common/event/EventBase.o \
       common/event/WallRecognizerEvent.o \
       sam/WallRecognizer.o \
       sam/MapRepo.o sam/MazeMapper.o sam/PathPlanner.o \
       sensorreadloop/SensorReader.o sensorreadloop/SonarFront.o \
       sensorreadloop/FlightSensorLeft.o sensorreadloop/FlightSensorRight.o \
       sensorreadloop/SensorData.o \
       test/MainController.o main.o

LIBS =

TARGET = AMSS

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

clean:
	rm -rf $(OBJS) $(TARGET) 
