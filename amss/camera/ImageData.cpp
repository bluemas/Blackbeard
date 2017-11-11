// Image Data Class Source File

#include "ImageData.h"
#include <stdio.h>
#include <cstring>

using namespace std;

ImageData* ImageData::mImageData = 0;

ImageData::ImageData() {

}
ImageData::~ImageData() {

}

ImageData* ImageData::getInstance()
{
    if(mImageData == 0)
    {
        //Guard<Thread_Mutex> guard(singleton_lock_);
        //if(mImageData == 0)
            mImageData = new ImageData();
        //Destructor release lock automatically
    }
    return mImageData;
}

void ImageData::writeData(unsigned char *buf, size_t length) {
    if (length > BUFSIZE) {
        printf("Cannot write : image length is larger than buffer size\n");
        printf("(buf size %d, img length %lu\n", BUFSIZE, length);
        return;
    }
    
    memcpy (mBuf, buf, length);
    mImgLength = length;
}

int ImageData::readData(unsigned char *buf, size_t BufSize) {
    if (BufSize <mImgLength) {
         printf("Cannot copy to destination buffer :\n");
         printf("Buffer size is smaller than image size\n"); 
         printf("(buf size %lu, img length %lu)\n",BufSize, mImgLength);
        return -1;      
    }
    memcpy(buf, mBuf, mImgLength);
    return mImgLength;
}

