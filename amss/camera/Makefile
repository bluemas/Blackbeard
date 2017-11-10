CXXFLAGS=-O2 -g -Wall -std=gnu++11 -I../common

OBJS =  CameraReader.o \
		DotRecognizer.o \
		ImageRecognizer.o \
		LineRecognizer.o \
		SignRecognizer.o \
		SquareRecognizer.o

LIBS =

COM_HEADER_DIR = ../common

INC = -I$(COM_HEADER_DIR)

TARGET = camera.a

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rc $(TARGET) $(OBJS)

clean:
	rm -rf $(OBJS) $(TARGET) 
