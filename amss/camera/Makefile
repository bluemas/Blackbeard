CXXFLAGS=-O2 -g -Wall -std=gnu++11 -I../common

OBJS_CAM_LIB =  CameraReader.o \
				DotRecognizer.o \
				ImageRecognizer.o \
				LineRecognizer.o \
				SignRecognizer.o \
				SquareRecognizer.o \
				ImageData.o \
				../common/event/EventBase.o \
				../common/event/LineRecognizedEvent.o \
				../common/event/LineRecognizedEventHandler.o \
				../common/event/RedDotRecognizedEvent.o \
				../common/event/RedDotRecognizedEventHandler.o \
				../common/event/SignRecognizedEvent.o \
				../common/event/SignRecognizedEventHandler.o \
				../common/event/SquareRecognizedEvent.o \
				../common/event/SquareRecognizedEventHandler.o


OBJS_IMG_RECOG_TEST = ImageRecognizerTest.o

LIBS = -lpthread -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_video -lopencv_videoio -L/usr/local/lib


COM_HEADER_DIR = ../common \
				/usr/local/include

INC = -I../common \
	  -I/usr/local/include

TARGET = camera.a
TEST = image_recognizer_test


all: $(TARGET) $(TEST)

test: $(TEST)

$(TARGET): $(OBJS_CAM_LIB)
	$(AR) rc $(TARGET) $(OBJS_CAM_LIB)

$(TEST): $(OBJS_IMG_RECOG_TEST) $(TARGET)
	$(CXX) -o $(TEST) $(OBJS_IMG_RECOG_TEST) $(TARGET) $(LIBS) $(CXXFLAGS) $(INC)

clean:
	rm -rf $(OBJS_CAM_LIB) $(OBJS_IMG_RECOG_TEST) $(TARGET) $(TEST)
