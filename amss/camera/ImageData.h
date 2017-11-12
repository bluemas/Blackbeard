// Image Data Class Header File

#ifndef _IMAGE_DATA_H_
#define _IMAGE_DATA_H_

#include <map>
#include "../common/Constants.h"

using namespace std;
#define BUFSIZE (1024*64)

class ImageData {
    
public:
    ~ImageData();
    static ImageData* getInstance();

    void writeData(unsigned char *buf, size_t length);
    int readData(unsigned char *buf, size_t bufSize); //return value is image size
    int getImageSize();

private:
    unsigned char mBuf[BUFSIZE];
    size_t mImgLength;
    static ImageData* mImageData;

    ImageData();

};

#endif
