CXXFLAGS=-O2 -g -Wall -std=gnu++11 -lpthread

OBJS = common/EventBase.o sam/WallRecognizer.o sam/WallRecognizerEvent.o test/MainController.o main.o

LIBS =

TARGET = AMSS

all: $(TARGET)

$(TARGET): $(OBJS)
        $(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

clean:
        rm -rf $(OBJS) $(TARGET)