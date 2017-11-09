CXXFLAGS=-O2 -g -Wall -std=gnu++11 -lpthread

OBJS = common/EventHandlerAdapter.o common/EventBase.o common/SensingEventBase.o \
       common/WallRecognizerEvent.o \
       sam/WallRecognizer.o \
       sam/MapRepo.o sam/MazeMapper.o sam/PathPlanner.o \
       test/MainController.o main.o

LIBS =

TARGET = AMSS

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

clean:
	rm -rf $(OBJS) $(TARGET) 
